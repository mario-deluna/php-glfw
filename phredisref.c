#include "hiredis/hiredis.h"
#include "php_phpiredis.h"
#include "php_phpiredis_struct.h"

#include "ext/standard/head.h"
#include "ext/standard/info.h"

#define PHPIREDIS_CONNECTION_NAME "phpredis connection"
#define PHPIREDIS_PERSISTENT_CONNECTION_NAME "phpredis connection persistent"
#define PHPIREDIS_READER_NAME "phpredis reader"

int le_redis_reader_context;
int le_redis_context;
int le_redis_persistent_context;

#include <zend_API.h>

#ifdef ZEND_ENGINE_3
    #define PHPIREDIS_LEN_TYPE size_t
    #define PHPIREDIS_RESOURCE_TYPE zend_resource
    #define PHPIREDIS_RETURN_RESOURCE(connection, context) \
        RETURN_RES(zend_register_resource(connection, context))
#else
    #define PHPIREDIS_LEN_TYPE int
    #define PHPIREDIS_RESOURCE_TYPE zend_rsrc_list_entry
    #define PHPIREDIS_RETURN_RESOURCE(connection, context) \
        ZEND_REGISTER_RESOURCE(return_value, connection, context)
    typedef long zend_long;
#endif

typedef struct callback {
#ifdef ZEND_ENGINE_3
    zval function;
#else
    zval *function;
#endif
} callback;

// -------------------------------------------------------------------------- //

static void free_reader_status_callback(phpiredis_reader *reader TSRMLS_DC)
{
    if (reader->status_callback) {
        zval_ptr_dtor(&((callback*) reader->status_callback)->function);
        efree(reader->status_callback);
        reader->status_callback = NULL;
    }
}

static void set_reader_status_callback(phpiredis_reader *reader, zval *function TSRMLS_DC)
{
    free_reader_status_callback(reader TSRMLS_CC);

    reader->status_callback = emalloc(sizeof(callback));

#ifdef ZEND_ENGINE_3
    ZVAL_DUP(&((callback*) reader->status_callback)->function, function);
#else
    Z_ADDREF_P(function);
    ((callback*) reader->status_callback)->function = function;
#endif
}

static void free_reader_error_callback(phpiredis_reader *reader TSRMLS_DC)
{
    if (reader->error_callback) {
        zval_ptr_dtor(&((callback*) reader->error_callback)->function);
        efree(reader->error_callback);
        reader->error_callback = NULL;
    }
}

static void set_reader_error_callback(phpiredis_reader *reader, zval *function TSRMLS_DC)
{
    free_reader_error_callback(reader TSRMLS_CC);

    reader->error_callback = emalloc(sizeof(callback));

#ifdef ZEND_ENGINE_3
    ZVAL_DUP(&((callback*) reader->error_callback)->function, function);
#else
    Z_ADDREF_P(function);
    ((callback*) reader->error_callback)->function = function;
#endif
}

static void get_command_arguments(zval *arr, char ***elements, size_t **elementslen, int *size)
{
#ifdef ZEND_ENGINE_3
    zval *p_zv;
#else
    HashPosition pos;
    zval **tmp;
    zval temp;
#endif

    int currpos = 0;

    *size = zend_hash_num_elements(Z_ARRVAL_P(arr));
    *elements = emalloc(sizeof(char*) * (*size));
    *elementslen = emalloc(sizeof(size_t) * (*size));

#ifdef ZEND_ENGINE_3
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), p_zv) {
        zend_string *str = zval_get_string(p_zv);

        (*elementslen)[currpos] = (size_t) str->len;
        (*elements)[currpos] = emalloc(sizeof(char) * (*elementslen)[currpos]);
        memcpy((*elements)[currpos], str->val, (*elementslen)[currpos]);

        ++currpos;

        zend_string_release(str);
    } ZEND_HASH_FOREACH_END();
#else
    zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(arr), &pos);
    while (zend_hash_get_current_data_ex(Z_ARRVAL_P(arr), (void **) &tmp, &pos) == SUCCESS) {
        temp = **tmp;
        zval_copy_ctor(&temp);
        convert_to_string(&temp);

        (*elementslen)[currpos] = (size_t) Z_STRLEN(temp);
        (*elements)[currpos] = emalloc(sizeof(char) * (*elementslen)[currpos]);
        memcpy((*elements)[currpos], Z_STRVAL(temp), (*elementslen)[currpos]);

        ++currpos;

        zval_dtor(&temp);
        zend_hash_move_forward_ex(Z_ARRVAL_P(arr), &pos);
    }
#endif
}

static void free_command_arguments(char ***elements, size_t **elementslen, int *size)
{
    for (; *size > 0; --*size) {
        efree((*elements)[*size-1]);
    }
    efree((*elements));
    efree((*elementslen));
}

static void convert_redis_to_php(phpiredis_reader *reader, zval *return_value, redisReply *reply TSRMLS_DC)
{
    //int type; /* REDIS_REPLY_* */
    //long long integer; /* The integer when type is REDIS_REPLY_INTEGER */
    //int len; /* Length of string */
    //char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
    //size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
    //struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */

    switch (reply->type) {
        case REDIS_REPLY_INTEGER:
            ZVAL_LONG(return_value, reply->integer);
            return;

        case REDIS_REPLY_ERROR:
        case REDIS_REPLY_STATUS:
            if (reader != NULL) {
                if (reply->type == REDIS_REPLY_ERROR && reader->error_callback != NULL) {
#ifdef ZEND_ENGINE_3
                    zval arg[1];
                    ZVAL_STRINGL(&arg[0], reply->str, reply->len);

                    if (call_user_function(EG(function_table), NULL, &((callback*) reader->error_callback)->function, return_value, 1, arg TSRMLS_CC) == FAILURE) {
                        zval_ptr_dtor(return_value);
                        ZVAL_NULL(return_value);
                    }
#else
                    zval *arg[1];
                    MAKE_STD_ZVAL(arg[0]);
                    ZVAL_STRINGL(arg[0], reply->str, reply->len, 1);

                    if (call_user_function(EG(function_table), NULL, ((callback*) reader->error_callback)->function, return_value, 1, arg TSRMLS_CC) == FAILURE) {
                        zval_ptr_dtor(&return_value);
                        ZVAL_NULL(return_value);
                    }
#endif
                    zval_ptr_dtor(&arg[0]);

                    return;
                } else if (reply->type == REDIS_REPLY_STATUS && reader->status_callback != NULL) {
#ifdef ZEND_ENGINE_3
                    zval arg[1];
                    ZVAL_STRINGL(&arg[0], reply->str, reply->len);

                    if (call_user_function(EG(function_table), NULL, &((callback*) reader->status_callback)->function, return_value, 1, arg TSRMLS_CC) == FAILURE) {
                        zval_ptr_dtor(return_value);
                        ZVAL_NULL(return_value);
                    }
#else
                    zval *arg[1];
                    MAKE_STD_ZVAL(arg[0]);
                    ZVAL_STRINGL(arg[0], reply->str, reply->len, 1);

                    if (call_user_function(EG(function_table), NULL, ((callback*) reader->status_callback)->function, return_value, 1, arg TSRMLS_CC) == FAILURE) {
                        zval_ptr_dtor(&return_value);
                        ZVAL_NULL(return_value);
                    }
#endif
                    zval_ptr_dtor(&arg[0]);

                    return;
                }
            }
            // NO BREAK! For status and error returning the string content

        case REDIS_REPLY_STRING:
#ifdef ZEND_ENGINE_3
            ZVAL_STRINGL(return_value, reply->str, reply->len);
#else
            ZVAL_STRINGL(return_value, reply->str, reply->len, 1);
#endif
            return;

        case REDIS_REPLY_ARRAY: {
#ifdef ZEND_ENGINE_3
                zval val;
#else
                zval *val;
#endif
                int j;

                array_init(return_value);
                for (j = 0; j < reply->elements; j++) {
#ifdef ZEND_ENGINE_3
                    convert_redis_to_php(reader, &val, reply->element[j] TSRMLS_CC);
                    add_index_zval(return_value, j, &val);
#else
                    MAKE_STD_ZVAL(val);
                    convert_redis_to_php(reader, val, reply->element[j] TSRMLS_CC);
                    add_index_zval(return_value, j, val);
#endif
                }
            }
            return;

        case REDIS_REPLY_NIL:
        default:
            ZVAL_NULL(return_value);
            return;
    }
}

static void get_pipeline_responses(phpiredis_connection *connection, zval *return_value, int commands TSRMLS_DC)
{
    int i;

    for (i = 0; i < commands; ++i) {
        redisReply *reply = NULL;

#ifdef ZEND_ENGINE_3
        zval result;
        zval *p_result = &result;
#else
        zval *p_result;
        MAKE_STD_ZVAL(p_result);
#endif

        if (redisGetReply(connection->ctx, (void *)&reply) != REDIS_OK) {
            for (; i < commands; ++i) {
                add_index_bool(return_value, i, 0);
            }

            if (reply) freeReplyObject(reply);
#ifndef ZEND_ENGINE_3
            efree(p_result);
#endif
            break;
        }

        convert_redis_to_php(NULL, p_result, reply TSRMLS_CC);
        add_index_zval(return_value, i, p_result);

        freeReplyObject(reply);
    }
}

static void s_destroy_connection(phpiredis_connection *connection TSRMLS_DC)
{
    if (connection) {
        pefree(connection->ip, connection->is_persistent);
        if (connection->ctx != NULL) {
            redisFree(connection->ctx);
        }
        pefree(connection, connection->is_persistent);
    }
}

static void php_redis_connection_dtor(PHPIREDIS_RESOURCE_TYPE *rsrc TSRMLS_DC)
{
    phpiredis_connection *connection = (phpiredis_connection*) rsrc->ptr;
    s_destroy_connection(connection TSRMLS_CC);
}

static void php_redis_reader_dtor(PHPIREDIS_RESOURCE_TYPE *rsrc TSRMLS_DC)
{
    phpiredis_reader *reader = (void *) rsrc->ptr;

    if (reader) {
        if (reader->bufferedReply != NULL) {
            freeReplyObject(reader->bufferedReply);
        }

        if (reader->reader != NULL) {
            redisReplyReaderFree(reader->reader);
        }

        free_reader_status_callback(reader TSRMLS_CC);
        free_reader_error_callback(reader TSRMLS_CC);

        efree(reader);
    }
}

static phpiredis_connection *fetch_resource_connection(zval *resource TSRMLS_DC)
{
    phpiredis_connection *connection;

#ifdef ZEND_ENGINE_3
    connection = (phpiredis_connection *)zend_fetch_resource2_ex(resource, PHPIREDIS_CONNECTION_NAME, le_redis_context, le_redis_persistent_context);
#else
    ZEND_FETCH_RESOURCE2_NO_RETURN(connection, phpiredis_connection *, &resource, -1, PHPIREDIS_CONNECTION_NAME, le_redis_context, le_redis_persistent_context);
#endif

    return connection;
}

static phpiredis_reader *fetch_resource_reader(zval *resource TSRMLS_DC)
{
    phpiredis_reader *reader;

#ifdef ZEND_ENGINE_3
    reader = (phpiredis_reader *)zend_fetch_resource_ex(resource, PHPIREDIS_READER_NAME, le_redis_reader_context);
#else
    ZEND_FETCH_RESOURCE_NO_RETURN(reader, phpiredis_reader *, &resource, -1, PHPIREDIS_READER_NAME, le_redis_reader_context);
#endif

    return reader;
}

static phpiredis_connection *s_create_connection(const char *ip, int port, zend_long timeout, zend_bool is_persistent)
{
    redisContext *ctx;
    phpiredis_connection *connection;

    if (timeout > 0) {
        struct timeval tv;

        tv.tv_sec = timeout / 1000; /* msec to sec */
        tv.tv_usec = (timeout % 1000) * 1000; /* msec to usec */

        if (ip[0] == '/') {
            ctx = redisConnectUnixWithTimeout(ip, tv);
        } else {
            ctx = redisConnectWithTimeout(ip, port, tv);
        }
    } else if (ip[0] == '/') {
        // We ignore the value of "port" if the string value in "ip" starts with
        // a slash character indicating a UNIX domain socket path.
        ctx = redisConnectUnix(ip);
    } else {
        ctx = redisConnect(ip, port);
    }

    if (!ctx || ctx->err) {
        redisFree(ctx);
        return NULL;
    }

    connection                = pemalloc(sizeof(phpiredis_connection), is_persistent);
    connection->ctx           = ctx;
    connection->ip            = pestrdup(ip, is_persistent);
    connection->port          = port;
    connection->is_persistent = is_persistent;

    return connection;
}

// -------------------------------------------------------------------------- //

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_connect, 0, 0, 1)
    ZEND_ARG_INFO(0, ip)
    ZEND_ARG_INFO(0, port)
    ZEND_ARG_INFO(0, timeout_ms)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_connect)
{
    phpiredis_connection *connection;
    char *ip;
    PHPIREDIS_LEN_TYPE ip_size;
    zend_long port = 6379, timeout = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &ip, &ip_size, &port, &timeout) == FAILURE) {
        return;
    }

    connection = s_create_connection(ip, port, timeout, 0);

    if (!connection) {
        RETURN_FALSE;
    }

    PHPIREDIS_RETURN_RESOURCE(connection, le_redis_context);
}

PHP_FUNCTION(phpiredis_pconnect)
{
    char *ip;
    PHPIREDIS_LEN_TYPE ip_size;
    zend_long port = 6379, timeout;

    char *hashed_details = NULL;
    PHPIREDIS_LEN_TYPE hashed_details_length;
    phpiredis_connection *connection;
#ifdef ZEND_ENGINE_3
    zval *p_zval;
    zend_resource new_le;
#else
    zend_rsrc_list_entry new_le, *le;
#endif

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &ip, &ip_size, &port, &timeout) == FAILURE) {
        return;
    }

    hashed_details_length = spprintf(&hashed_details, 0, "phpiredis_%s_%d", ip, (int)port);

#ifdef ZEND_ENGINE_3
    p_zval = zend_hash_str_find_ptr(&EG(persistent_list), hashed_details, hashed_details_length);

    if (p_zval != NULL) {
        if (Z_RES_P(p_zval)->type != le_redis_persistent_context) {
            RETURN_FALSE;
        }
        connection = (phpiredis_connection *) Z_RES_P(p_zval)->ptr;
#else
    if (zend_hash_find(&EG(persistent_list), hashed_details, hashed_details_length+1, (void **) &le)!=FAILURE) {
        if (Z_TYPE_P(le) != le_redis_persistent_context) {
            RETURN_FALSE;
        }
        connection = (phpiredis_connection *) le->ptr;
#endif
        efree(hashed_details);
        PHPIREDIS_RETURN_RESOURCE(connection, le_redis_persistent_context);
        return;
    }

    connection = s_create_connection(ip, port, timeout, 1);

    if (!connection) {
        efree(hashed_details);
        RETURN_FALSE;
    }

    new_le.type = le_redis_persistent_context;
    new_le.ptr = connection;

#ifdef ZEND_ENGINE_3
    if (zend_hash_str_update_mem(&EG(persistent_list), hashed_details, hashed_details_length, &new_le, sizeof(zend_resource)) == NULL) {
#else
    if (zend_hash_update(&EG(persistent_list), hashed_details, hashed_details_length+1, (void *) &new_le, sizeof(zend_rsrc_list_entry), NULL)==FAILURE) {
#endif

        s_destroy_connection (connection TSRMLS_CC);
        efree(hashed_details);
        RETURN_FALSE;
    }

    efree(hashed_details);

    PHPIREDIS_RETURN_RESOURCE(connection, le_redis_persistent_context);
}

PHP_FUNCTION(phpiredis_disconnect)
{
    zval *resource;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource) == FAILURE) {
        RETURN_FALSE;
    }

    if (fetch_resource_connection(resource TSRMLS_CC) == NULL) {
        RETURN_FALSE;
    }

#ifdef ZEND_ENGINE_3
    zend_list_close(Z_RES_P(resource));
#else
    zend_list_delete(Z_LVAL_P(resource));
#endif

    RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_multi_command, 0, 0, 2)
    ZEND_ARG_INFO(0, connection)
    ZEND_ARG_ARRAY_INFO(0, commands, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_multi_command)
{
    zval *resource, *cmds;
    phpiredis_connection *connection;

#ifdef ZEND_ENGINE_3
    zval *p_zval;
#else
    HashPosition pos;
    zval **tmp;
    zval temp;
#endif

    int commands = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ra", &resource, &cmds) == FAILURE) {
        return;
    }

    connection = fetch_resource_connection(resource TSRMLS_CC);
    if (connection == NULL) {
        RETURN_FALSE;
    }

#ifdef ZEND_ENGINE_3
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(cmds), p_zval) {
        redisAppendCommand(connection->ctx, Z_STRVAL_P(p_zval));

        ++commands;
    } ZEND_HASH_FOREACH_END();
#else
    zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(cmds), &pos);
    while (zend_hash_get_current_data_ex(Z_ARRVAL_P(cmds), (void **) &tmp, &pos) == SUCCESS) {
        temp = **tmp;
        zval_copy_ctor(&temp);
        convert_to_string(&temp);

        redisAppendCommand(connection->ctx, Z_STRVAL(temp));

        ++commands;

        zval_dtor(&temp);
        zend_hash_move_forward_ex(Z_ARRVAL_P(cmds), &pos);
    }
#endif

    array_init(return_value);
    get_pipeline_responses(connection, return_value, commands TSRMLS_CC);
}

PHP_FUNCTION(phpiredis_multi_command_bs)
{
    zval *resource, *cmds;
    phpiredis_connection *connection;
    zval *p_cmdArgs;
#ifndef ZEND_ENGINE_3
    zval cmdArgs;
    HashPosition cmdsPos;
    zval **tmp;
#endif
    int cmdSize;
    char **cmdElements;
    size_t *cmdElementslen;

    int commands;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ra", &resource, &cmds) == FAILURE) {
        return;
    }

    connection = fetch_resource_connection(resource TSRMLS_CC);
    if (connection == NULL) {
        RETURN_FALSE;
    }

    commands = 0;

#ifdef ZEND_ENGINE_3
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(cmds), p_cmdArgs) {
#else

    zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(cmds), &cmdsPos);
    while (zend_hash_get_current_data_ex(Z_ARRVAL_P(cmds), (void **) &tmp, &cmdsPos) == SUCCESS) {
        cmdArgs = **tmp;
        p_cmdArgs = &cmdArgs;
        zval_copy_ctor(p_cmdArgs);
#endif
        get_command_arguments(p_cmdArgs, &cmdElements, &cmdElementslen, &cmdSize);
        redisAppendCommandArgv(connection->ctx, cmdSize, (const char **)cmdElements, cmdElementslen);

        free_command_arguments(&cmdElements, &cmdElementslen, &cmdSize);

        ++commands;

#ifdef ZEND_ENGINE_3
    } ZEND_HASH_FOREACH_END();
#else
        zval_dtor(&cmdArgs);
        zend_hash_move_forward_ex(Z_ARRVAL_P(cmds), &cmdsPos);
    }
#endif

    array_init(return_value);
    get_pipeline_responses(connection, return_value, commands TSRMLS_CC);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_command, 0, 0, 2)
    ZEND_ARG_INFO(0, connection)
    ZEND_ARG_INFO(0, command)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_command)
{
    zval *resource;
    redisReply *reply = NULL;
    phpiredis_connection *connection;
    char *command;
    PHPIREDIS_LEN_TYPE command_size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &resource, &command, &command_size) == FAILURE) {
        return;
    }

    connection = fetch_resource_connection(resource TSRMLS_CC);
    if (connection == NULL) {
        RETURN_FALSE;
    }

    reply = redisCommand(connection->ctx, command);
    if (reply == NULL) {
        RETURN_FALSE;
    }

    if (reply->type == REDIS_REPLY_ERROR) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", reply->str);
        freeReplyObject(reply);

        RETURN_FALSE;
    }

    convert_redis_to_php(NULL, return_value, reply TSRMLS_CC);
    freeReplyObject(reply);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_command_bs, 0, 0, 2)
    ZEND_ARG_INFO(0, connection)
    ZEND_ARG_ARRAY_INFO(0, args, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_command_bs)
{
    zval *resource;
    zval *cmdArgs;
    phpiredis_connection *connection;

    redisReply *reply = NULL;

    int cmdSize;
    char **cmdElements;
    size_t *cmdElementslen;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ra", &resource, &cmdArgs) == FAILURE) {
        return;
    }

    connection = fetch_resource_connection(resource TSRMLS_CC);
    if (connection == NULL) {
        RETURN_FALSE;
    }

    get_command_arguments(cmdArgs, &cmdElements, &cmdElementslen, &cmdSize);
    redisAppendCommandArgv(connection->ctx, cmdSize, (const char **)cmdElements, cmdElementslen);

    free_command_arguments(&cmdElements, &cmdElementslen, &cmdSize);

    if (redisGetReply(connection->ctx, (void **)&reply) != REDIS_OK) {
        // only free if the reply was actually created
        if (reply) freeReplyObject(reply);

        RETURN_FALSE;
    }

    if (reply->type == REDIS_REPLY_ERROR) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", reply->str);
        freeReplyObject(reply);

        RETURN_FALSE;
    }

    convert_redis_to_php(NULL, return_value, reply TSRMLS_CC);

    freeReplyObject(reply);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_format_command, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, args, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_format_command)
{
    zval *cmdArgs;

    char *cmd;
    int cmdlen;
    int cmdSize;
    char **cmdElements;
    size_t *cmdElementslen;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &cmdArgs) == FAILURE) {
        return;
    }

    get_command_arguments(cmdArgs, &cmdElements, &cmdElementslen, &cmdSize);
    cmdlen = redisFormatCommandArgv(&cmd, cmdSize, (const char **)cmdElements, cmdElementslen);

#ifdef ZEND_ENGINE_3
    ZVAL_STRINGL(return_value, cmd, cmdlen);
#else
    ZVAL_STRINGL(return_value, cmd, cmdlen, 1);
#endif

    free_command_arguments(&cmdElements, &cmdElementslen, &cmdSize);
    free(cmd);
}

PHP_FUNCTION(phpiredis_reader_create)
{
    phpiredis_reader *reader;

    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_FALSE;
    }

    reader = emalloc(sizeof(phpiredis_reader));
    reader->reader = redisReplyReaderCreate();
    reader->error = NULL;
    reader->bufferedReply = NULL;
    reader->status_callback = NULL;
    reader->error_callback = NULL;

    PHPIREDIS_RETURN_RESOURCE(reader, le_redis_reader_context);
}

PHP_FUNCTION(phpiredis_reader_set_status_handler)
{
    zval *resource, *function = NULL;
    phpiredis_reader *reader;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &resource, &function) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

#ifdef ZEND_ENGINE_3
    ZVAL_DEREF(function);
#endif

    if (Z_TYPE_P(function) == IS_NULL) {
        free_reader_status_callback(reader TSRMLS_CC);
    } else {
        if (!zend_is_callable(function, 0, NULL TSRMLS_CC)) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Argument is not a valid callback");
            RETURN_FALSE;
        }

        set_reader_status_callback(reader, function TSRMLS_CC);
    }

    RETURN_TRUE;
}

PHP_FUNCTION(phpiredis_reader_set_error_handler)
{
    zval *resource, *function = NULL;
    phpiredis_reader *reader;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &resource, &function) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

#ifdef ZEND_ENGINE_3
    ZVAL_DEREF(function);
#endif

    if (Z_TYPE_P(function) == IS_NULL) {
        free_reader_error_callback(reader TSRMLS_CC);
    } else {
        if (!zend_is_callable(function, 0, NULL TSRMLS_CC)) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Argument is not a valid callback");
            RETURN_FALSE;
        }

        set_reader_error_callback(reader, function TSRMLS_CC);
    }

    RETURN_TRUE;
}

PHP_FUNCTION(phpiredis_reader_reset)
{
    zval *resource;
    phpiredis_reader *reader;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        return;
    }

    if (reader->bufferedReply != NULL) {
        freeReplyObject(reader->bufferedReply);
        reader->bufferedReply = NULL;
    }

    if (reader->reader != NULL) {
        redisReplyReaderFree(reader->reader);
    }

    reader->reader = redisReplyReaderCreate();
}

PHP_FUNCTION(phpiredis_reader_destroy)
{
    zval *resource;
    phpiredis_reader *reader;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

#ifdef ZEND_ENGINE_3
    zend_list_close(Z_RES_P(resource));
#else
    zend_list_delete(Z_LVAL_P(resource));
#endif

    RETURN_TRUE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_reader_feed, 0, 0, 2)
    ZEND_ARG_INFO(0, connection)
    ZEND_ARG_INFO(0, buffer)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_reader_feed)
{
    zval *resource;
    phpiredis_reader *reader;
    char *bytes;
    PHPIREDIS_LEN_TYPE size;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &resource, &bytes, &size) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

    redisReplyReaderFeed(reader->reader, bytes, size);
}

PHP_FUNCTION(phpiredis_reader_get_error)
{
    zval *resource;
    phpiredis_reader *reader;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

    if (reader->error == NULL) {
        RETURN_FALSE;
    }

#ifdef ZEND_ENGINE_3
    ZVAL_STRINGL(return_value, reader->error, strlen(reader->error));
#else
    ZVAL_STRINGL(return_value, reader->error, strlen(reader->error), 1);
#endif
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_reader_get_reply, 0, 0, 1)
    ZEND_ARG_INFO(0, ptr)
    ZEND_ARG_INFO(1, type)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_reader_get_reply)
{
    zval *resource, *replyType = NULL;
    phpiredis_reader *reader;
    redisReply *aux;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|z/", &resource, &replyType) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

    if (reader->bufferedReply) {
        aux = reader->bufferedReply;
        reader->bufferedReply = NULL;
    } else {
        if (redisReplyReaderGetReply(reader->reader, (void **)&aux) == REDIS_ERR) {
            if (reader->error != NULL) {
                efree(reader->error);
            }
            reader->error = redisReplyReaderGetError(reader->reader);

            RETURN_FALSE; // error
        } else if (aux == NULL) {
            RETURN_FALSE; // incomplete
        }
    }

    convert_redis_to_php(reader, return_value, aux TSRMLS_CC);

    if (ZEND_NUM_ARGS() > 1) {
        zval_dtor(replyType);
        ZVAL_LONG(replyType, aux->type);
    }

    freeReplyObject(aux);
}

PHP_FUNCTION(phpiredis_reader_get_state)
{
    zval *resource;
    phpiredis_reader *reader;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &resource) == FAILURE) {
        return;
    }

    reader = fetch_resource_reader(resource TSRMLS_CC);
    if (reader == NULL) {
        RETURN_FALSE;
    }

    if (reader->error == NULL && reader->bufferedReply == NULL) {
        void *aux;

        if (redisReplyReaderGetReply(reader->reader, &aux) == REDIS_ERR) {
            if (reader->error != NULL) {
                efree(reader->error);
            }
            reader->error = redisReplyReaderGetError(reader->reader);
        } else {
            reader->bufferedReply = aux;
        }
    }

    if (reader->error != NULL) {
        ZVAL_LONG(return_value, PHPIREDIS_READER_STATE_ERROR);
    } else if (reader->bufferedReply != NULL) {
        ZVAL_LONG(return_value, PHPIREDIS_READER_STATE_COMPLETE);
    } else {
        ZVAL_LONG(return_value, PHPIREDIS_READER_STATE_INCOMPLETE);
    }
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_utils_crc16, 0, 0, 1)
    ZEND_ARG_INFO(0, buffer)
ZEND_END_ARG_INFO()

PHP_FUNCTION(phpiredis_utils_crc16)
{
    char *buf;
    PHPIREDIS_LEN_TYPE buf_size;
    uint16_t crc;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &buf, &buf_size) == FAILURE) {
        return;
    }

    crc = crc16(buf, buf_size);

    ZVAL_LONG(return_value, crc);
}

// -------------------------------------------------------------------------- //

PHP_MINIT_FUNCTION(phpiredis)
{
    le_redis_context = zend_register_list_destructors_ex(php_redis_connection_dtor, NULL, PHPIREDIS_CONNECTION_NAME, module_number);
    le_redis_persistent_context = zend_register_list_destructors_ex(NULL, php_redis_connection_dtor, PHPIREDIS_PERSISTENT_CONNECTION_NAME, module_number);
    le_redis_reader_context = zend_register_list_destructors_ex(php_redis_reader_dtor, NULL, PHPIREDIS_READER_NAME, module_number);

    REGISTER_LONG_CONSTANT("PHPIREDIS_READER_STATE_INCOMPLETE", PHPIREDIS_READER_STATE_INCOMPLETE, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_READER_STATE_COMPLETE", PHPIREDIS_READER_STATE_COMPLETE, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_READER_STATE_ERROR", PHPIREDIS_READER_STATE_ERROR, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_REPLY_STRING", REDIS_REPLY_STRING, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_REPLY_ARRAY", REDIS_REPLY_ARRAY, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_REPLY_INTEGER", REDIS_REPLY_INTEGER, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_REPLY_NIL", REDIS_REPLY_NIL, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_REPLY_STATUS", REDIS_REPLY_STATUS, CONST_PERSISTENT|CONST_CS);
    REGISTER_LONG_CONSTANT("PHPIREDIS_REPLY_ERROR", REDIS_REPLY_ERROR, CONST_PERSISTENT|CONST_CS);

    return SUCCESS;
}

/* arginfo shared by various functions */

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_conn, 0, 0, 1)
    ZEND_ARG_INFO(0, connection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_phpiredis_callback, 0, 0, 2)
    ZEND_ARG_INFO(0, connection)
    ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()


static zend_function_entry phpiredis_functions[] = {
    PHP_FE(phpiredis_connect, arginfo_phpiredis_connect)
    PHP_FE(phpiredis_pconnect, arginfo_phpiredis_connect)
    PHP_FE(phpiredis_disconnect, arginfo_phpiredis_conn)
    PHP_FE(phpiredis_command, arginfo_phpiredis_command)
    PHP_FE(phpiredis_command_bs, arginfo_phpiredis_command_bs)
    PHP_FE(phpiredis_multi_command, arginfo_phpiredis_multi_command)
    PHP_FE(phpiredis_multi_command_bs, arginfo_phpiredis_multi_command)
    PHP_FE(phpiredis_format_command, arginfo_phpiredis_format_command)
    PHP_FE(phpiredis_reader_create, arginfo_phpiredis_void)
    PHP_FE(phpiredis_reader_reset, arginfo_phpiredis_conn)
    PHP_FE(phpiredis_reader_feed, arginfo_phpiredis_reader_feed)
    PHP_FE(phpiredis_reader_get_state, arginfo_phpiredis_conn)
    PHP_FE(phpiredis_reader_get_error, arginfo_phpiredis_conn)
    PHP_FE(phpiredis_reader_get_reply, arginfo_phpiredis_reader_get_reply)
    PHP_FE(phpiredis_reader_destroy, arginfo_phpiredis_conn)
    PHP_FE(phpiredis_reader_set_error_handler, arginfo_phpiredis_callback)
    PHP_FE(phpiredis_reader_set_status_handler, arginfo_phpiredis_callback)
    PHP_FE(phpiredis_utils_crc16, arginfo_phpiredis_utils_crc16)
#ifdef PHP_FE_END
    PHP_FE_END
#else
    {NULL, NULL, NULL}
#endif
};

static PHP_MINFO_FUNCTION(phpiredis)
{
    char buf[32];

    php_info_print_table_start();

    php_info_print_table_row(2, "phpiredis", "enabled");
    php_info_print_table_row(2, "phpiredis version", PHP_PHPIREDIS_VERSION);
    snprintf(buf, sizeof(buf), "%d.%d.%d", HIREDIS_MAJOR, HIREDIS_MINOR, HIREDIS_PATCH);
    php_info_print_table_row(2, "hiredis version", buf);

    php_info_print_table_end();
}

zend_module_entry phpiredis_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_PHPIREDIS_EXTNAME,
    phpiredis_functions,
    PHP_MINIT(phpiredis),
    NULL,
    NULL,
    NULL,
    PHP_MINFO(phpiredis),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_PHPIREDIS_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHPIREDIS
ZEND_GET_MODULE(phpiredis)
#endif