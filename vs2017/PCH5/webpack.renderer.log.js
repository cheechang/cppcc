/**
 * webpack自带的核心插件UglifyJsPlugin，用来压缩输出文件，过滤日志
 */
const webpack = require('webpack')
const path = require('path')
module.exports = {
  plugins: [
    new webpack.optimize.UglifyJsPlugin({
      output: {
        beautify: false,
        comments: false
      },
      compress: {
        dead_code: true,
        warnings:false,
        drop_debugger: !global.openDebugModel,
        drop_console: !global.openDebugModel,
        loops: true
      },
      sourceMap: false
    })
  ],
  module: {
    rules: [{
        test: /\.vue$/,
        use: {
          loader: 'vue-loader',
          options: {
            loaders: {
              scss: [
                'vue-style-loader',
                'css-loader',
                'sass-loader',
                {
                  loader: 'sass-resources-loader',
                  options: {
                    resources: './src/renderer/style/global.scss',
                  },
                }
              ]
            }
          }
        }
      },
      {
        test: /\.(webp)(\?.*)?$/,
        loader: 'url-loader'
      }
    ]
  },
  resolve: {
    alias: {
      'Theme': path.resolve(__dirname, 'src/renderer/style/theme')
    }
  }
}
