function render() {
  with (this) {
    return _c(
      "div",
      {
        attrs: {
          id: "app",
        },
      },
      [
        _c("input", {
          directives: [
            {
              name: "model",
              rawName: "v-model",
              value: name,
              expression: "name",
            },
          ],
          attrs: {
            type: "text",
            name: "",
            id: "",
          },
          domProps: {
            value: name,
          },
          on: {
            input: function ($event) {
              if ($event.target.composing) return;
              name = $event.target.value;
            },
          },
        }),
        _c("span", [_v(_s(name) + " " + _s(address) + " : " + _s(inWhere))]),
      ]
    );
  }
}
