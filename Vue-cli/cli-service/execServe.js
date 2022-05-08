// api = new Plugins
module.exports = (api, options) => {
  // api.registerCommand就等于在this.command注册了serve函数
  api.registerCommand("serve", {
    description: "start development server",
    usage: "vue-cli-service serve [options] [entry]",
    options: {
      "--open": `open browser on server start`,
      "--copy": `copy url to clipboard on server start`,
      "--stdin": `close when stdin ends`,
      "--mode": `specify env mode (default: development)`,
      "--host": `specify host (default: ${defaults.host})`,
      "--port": `specify port (default: ${defaults.port})`,
      "--https": `use https (default: ${defaults.https})`,
      "--public": `specify the public network URL for the HMR client`,
      "--skip-plugins": `comma-separated list of plugin names to skip for this run`,
    },
  });
};
