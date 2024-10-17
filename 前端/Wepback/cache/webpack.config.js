const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  mode: "development",
  entry: path.resolve(__dirname, "./src/index.js"),
  plugins: [
    new HtmlWebpackPlugin({
      title: "Output Management",
      title: "Caching",
    }),
  ],
  output: {
    filename: "bundle.js",
    filename: "[name].[chunkhash].js",
    path: path.resolve(__dirname, "dist"),
    clean: true,
  },
};
