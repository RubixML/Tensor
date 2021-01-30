<?php

namespace Zephir\Optimizers\FunctionCall;

use Zephir\Call;
use Zephir\CompilationContext;
use Zephir\CompiledExpression;
use Zephir\HeadersManager;
use Zephir\Exception\CompilerException;
use Zephir\Optimizers\OptimizerAbstract;

class ArrayModOptimizer extends OptimizerAbstract
{
    /**
     * @param mixed[] $expression
     * @param \Zephir\Call $call
     * @param \Zephir\CompilationContext $context
     * @throws \Zephir\Exception\CompilerException
     * @return \Zephir\CompiledExpression|bool
     */
    public function optimize(array $expression, Call $call, CompilationContext $context)
    {
        if (!isset($expression['parameters'])) {
            return false;
        }

        if (count($expression['parameters']) !== 2) {
            throw new CompilerException(
                'ArrayMod only accepts two argument.',
                $expression
            );
        }

        $call->processExpectedReturn($context);

        $symbolVariable = $call->getSymbolVariable();

        if ($symbolVariable->getType() !== 'variable') {
            throw new CompilerException(
                'Returned values by functions can only be assigned to variant variables.',
                $expression
            );
        }

        if ($call->mustInitSymbolVariable()) {
            $symbolVariable->initVariant($context);
        }

        $context->headersManager->add(
            'include/array_arithmetic',
            HeadersManager::POSITION_LAST
        );

        $resolvedParams = $call->getResolvedParams(
            $expression['parameters'],
            $context,
            $expression
        );

        $symbol = $context->backend->getVariableCode($symbolVariable);

        $context->codePrinter->output(
            'tensor_array_mod(' . $symbol . ', ' . $resolvedParams[0] . ', ' . $resolvedParams[1] . ');'
        );

        return new CompiledExpression(
            'variable',
            $symbolVariable->getRealName(),
            $expression
        );
    }
}
