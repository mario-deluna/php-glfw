<?php

use PhpParser\Node;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\NodeTraverser;
use PhpParser\NodeVisitorAbstract;
use PhpParser\ParserFactory;
use PhpParser\Node\Stmt\Function_;
use PhpParser\NodeVisitor\NameResolver;
use PhpParser\NodeVisitor\ParentConnectingVisitor;

class ExtDocParser
{
    /**
     * The result of parsing the IDE stubs file
     * 
     * @var array<array{signature: ?string, comment: ?string}>
     */
    private array $stubsData = [];

    /**
     * Constructor
     */
    public function __construct()
    {
        $this->parseStubs();
    }

    /**
     * Parses our freshly generated stubs and returns an array of symbols 
     * with the method signature and the docblock comment
     */
    private function parseStubs() : void
    {
        $parser = (new ParserFactory)->create(ParserFactory::PREFER_PHP7);
        
        try {
            $ast = $parser->parse(file_get_contents(GEN_PATH_EXT . '/stubs/phpglfw.php'));
        } catch (Error $error) {
            throw new Exception("Failure to parse stub file for documentation generation...");
        }

        $traverser = new NodeTraverser();
        $traverser->addVisitor(new ParentConnectingVisitor);
        $traverser->addVisitor(new NameResolver(null, [
            'preserveOriginalNames' => false,
            'replaceNodes' => true,
        ]));

        $docBlockExtractor = new class extends NodeVisitorAbstract {
            public array $symbolData = [];
            
            private \phpDocumentor\Reflection\DocBlockFactory $docblockFactory;
            private \PhpParser\PrettyPrinter\Standard $prettyPrinter;

            public function __construct()
            {
                $this->docblockFactory = \phpDocumentor\Reflection\DocBlockFactory::createInstance();
                $this->prettyPrinter = new \PhpParser\PrettyPrinter\Standard;
            }

            public function leaveNode(Node $node) 
            {
                $symbol = null;
                $classNamespace = null; 

                if ($node instanceof Function_) {
                    $method = $node->name->toString();
                    $symbol = $method;
                }
                elseif ($node instanceof ClassMethod) {
                    $classNamespace = $node->getAttribute('parent')->namespacedName->toString();
                    $method = $node->name->toString();

                    $symbol = $classNamespace . '::' . $method;
                    
                }
                else {
                    return;
                }

                $this->symbolData[$symbol] = [
                    'namespace' => $classNamespace ?: null,
                    'function' => $method,
                    'signature' => null,
                    'comment' => null,
                    'docblock' => null,
                ];

                // extract the comment
                if ($node->getAttribute('comments') && $node->getAttribute('comments')[0]) {
                    $this->symbolData[$symbol]['comment'] = $node->getAttribute('comments')[0]->getText();

                    // parse the comment
                    $this->symbolData[$symbol]['docblock'] = $this->docblockFactory->create($this->symbolData[$symbol]['comment']);
                }
                
                // extract the signature
                $node->setAttribute('comments', []);
                $this->symbolData[$symbol]['signature'] = $this->prettyPrinter->prettyPrint([$node]);
            }
        };

        $traverser->addVisitor($docBlockExtractor);

        $ast = $traverser->traverse($ast);

        $this->stubsData = $docBlockExtractor->symbolData;
    }

    /**
     * Returns data for a given symbol, throws an exception if not found
     * 
     * @return array{signature: ?string, comment: ?string}
     */
    private function getSymbolData(string $symbol) : array
    {
        if (!isset($this->stubsData[$symbol])) {
            throw new Exception("Symbol {$symbol} could not be found in the stubs...");
        }

        return $this->stubsData[$symbol];
    }

    private function getSymbolDocBlock(string $symbol) : \phpDocumentor\Reflection\DocBlock
    {
        $data = $this->getSymbolData($symbol);
        if (!$data['docblock']) {
            throw new Exception("Symbol {$symbol} does not have a doc block.");
        }

        return $data['docblock'];
    }

    /**
     * Returns a simplyfied function Signature for a symbol
     * @return string 
     */
    public function getFunctionSignatureSimple(string $symbol) : string
    {
        $data = $this->getSymbolData($symbol);
        return trim(str_replace('public ', '', $data['signature']), "\n {}");
    }

    public function getSummary(string $symbol) : string
    {
        $docblock = $this->getSymbolDocBlock($symbol);   
        return $docblock->getSummary();
    }

    public function getAPIArgsMarkdown(string $symbol) : string
    {
        $docblock = $this->getSymbolDocBlock($symbol);   

        $paramTags = $docblock->getTagsByName('param');

        // no params nothing todo..
        if (count($paramTags) === 0) return '';

        $b = "arguments\n\n:";
        
        foreach($paramTags as $k => $paramTag) {
            $b .= tabulate(($k + 1) . '. `' . $paramTag->getType() . '` `$' . $paramTag->getVariableName() . '` ' .  $paramTag->getDescription()) . PHP_EOL;
        }

        return $b;
    }

    public function getAPIReturnMarkdown(string $symbol) : string
    {
        $docblock = $this->getSymbolDocBlock($symbol);   
        $returnTags = $docblock->getTagsByName('return');

        // no params nothing todo..
        if (count($returnTags) === 0) return '';

        $b = "returns\n\n:";
        
        foreach($returnTags as $returnTag) {
            $b .= '    `' . $returnTag->getType() . '` ' .  $returnTag->getDescription();
        }

        return $b;
    }

    public function getAPIRefMarkdown(string $symbol, array $options = []) : string
    {
        $data = $this->getSymbolData($symbol);

        $summary = $this->getSummary($symbol);
        $sig = $this->getFunctionSignatureSimple($symbol);

        $argsMd = $this->getAPIArgsMarkdown($symbol);
        $returnMd = $this->getAPIReturnMarkdown($symbol);

        $b = '';
        if (($options['no-title'] ?? false) !== true) {
            $b .= "### `{$data['function']}`\n\n";
        }

        $b .= <<<MARKDOWN
{$summary}

```php
{$sig}
```

{$argsMd}
{$returnMd}

---
    
MARKDOWN;

        return $b;
    }
}
