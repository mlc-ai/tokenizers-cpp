import { nodeResolve } from '@rollup/plugin-node-resolve';
import commonjs from '@rollup/plugin-commonjs';
import { wasm } from '@rollup/plugin-wasm';
import typescript from '@rollup/plugin-typescript';

export default {
    input: 'src/index.ts',
    output: {
        dir: 'dist',
        format: 'es'
    },
    plugins: [nodeResolve({ browser: true }), commonjs(), wasm(), typescript({ target: "es2017", downlevelIteration: true })]
};
