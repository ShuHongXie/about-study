<template></template>

<script>
export default {
  data() {
    return {};
  },
  mounted() {},
  methods: {
    render() {
      with (this) {
        return _c(
          "ul",
          _l(8, function (item, index) {
            return false
              ? _c(
                  "li",
                  {
                    key: index,
                  },
                  [
                    _c(
                      "button",
                      {
                        on: {
                          click: function ($event) {
                            return deleteSelectionCondition(index);
                          },
                        },
                      },
                      [_v("删除")]
                    ),
                  ]
                )
              : _e();
          }),
          0
        );
      }
    },
  },
};
</script>

<style lang="scss" scoped></style>
