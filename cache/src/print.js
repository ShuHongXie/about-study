export default function printMe() {
  console.log("I get called from print.js!1");
  import(/* webpackChunkName: "dynamic" */ "./dynamic").then((module) => {
    const dynamic = module.default;
    dynamic();
  });
}
