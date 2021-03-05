const path = require('path');
const webpack = require('webpack')
const HtmlWebpackPlugin = require('html-webpack-plugin');
// 清除文件
const CleanWebpackPlugin = require('clean-webpack-plugin');
module.exports = {
  entry: './src/renderer/emss.js',
  output: {
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'dist/emss')
  },
  module: {
      loaders:[
        {
          test: /\.vue$/,
          use: {
            loader: 'vue-loader',
            options: {
              esModule: true,
              loaders: {
                sass: 'vue-style-loader!css-loader!sass-loader?indentedSyntax=1',
                scss: 'vue-style-loader!css-loader!sass-loader'
              }
            }
          }
        },
        {
          test: /\.html$/,
          loader: "vue-html-loader"
        },
        {
          test: /\.css$/,
          loader: 'css-loader'
        },
        {
          test: /\.(png|jpe?g|gif|svg)(\?.*)?$/,
          loader: 'url-loader'
        },
        {
          test: /\.ts$/,
          loader: 'ts-loader',
          options: {
            appendTsSuffixTo: [/\.vue$/]
          }
        },
        {
          test: /\.(js)$/,
          use: 'babel-loader',
          exclude: /node_modules/
        },
        {
          test: /\.node$/,
          use: 'node-loader',
        },
        {
          test: /\.(woff2?|eot|ttf|otf)(\?.*)?$/,
          use: {
            loader: 'url-loader',
            query: {
              limit: 10000,
              name: 'fonts/[name].[ext]'
            }
          }
        }
    ]
  },
  plugins:[
    new HtmlWebpackPlugin({
      filename: 'index.html',
      template: path.resolve(__dirname, './src/indexEmss.ejs'),
      minify: {
        collapseWhitespace: true,
        removeAttributeQuotes: true,
        removeComments: true
      },
      nodeModules: process.env.NODE_ENV !== 'production'
        ? path.resolve(__dirname, './node_modules')
        : false
    }),
    // 删除文件 保留新文件
    new CleanWebpackPlugin(),
  ],
  resolve: {
    alias: {
      '@': path.join(__dirname, './src'),
      'vue$': 'vue/dist/vue.esm.js'
    },
    extensions: [".tsx", '.ts', '.js', '.vue', '.json', '.css', '.node', '.scss']
  }
};
