const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const path = require("path");

module.exports = {
  mode: "development",
  entry: path.join(__dirname, "index.js"),
  output: {
    path: path.resolve(__dirname, "./public"),
    filename: "main.js",
  },
  module: {
    rules: [
      {
        test: /\.s[ac]ss$/i,
        oneOf: [
          {
            resourceQuery: "?dark",
            use: [
              MiniCssExtractPlugin.loader,
              "css-loader",
              {
                loader: "sass-loader",
                options: {
                  additionalData: `@use './changeColor/dark-theme/_var.scss' as vars;`,
                },
              },
            ],
          },
          {
            use: [
              MiniCssExtractPlugin.loader,
              "css-loader",
              {
                loader: "sass-loader",
                options: {
                  additionalData: `@use './changeColor/light-theme/_var.scss' as vars;`,
                },
              },
            ],
          },
        ],
      },
    ],
  },
  plugins: [
    new MiniCssExtractPlugin({
      filename: "[name].css",
      attributes: {
        id: "theme",
      },
    }),
  ],
};
