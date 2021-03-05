/**
 * Created by lpy on 2017/10/24.
 */
export default {
  props: {
    size: String,
    expanded: Boolean,
    loading: Boolean,
    icon: String,
    iconPack: String,
    autocomplete: String,
    max: [Number, String],
    maxlength: [Number, String],
    min: [Number, String],
    minlength: [Number, String],
    required: Boolean,
    disabled: Boolean,
    name: String,
    placeholder: String,
    readonly: Boolean,
    rows: [Number, String]
  },

  data() {
    return {
      isValid: true
    };
  },
  computed: {
    parentField() {
      let parent = this.$parent;
      for (let i = 0; i < 3; i++) {
        if (parent && !parent.$data._isField) {
          parent = parent.$parent;
        }
      }
      return parent;
    },

    statusType() {
      if (!this.parentField) return;

      return this.parentField.newType;
    }
  },
  methods: {
    focus() {
      if (this.$refs[this.$data._elementRef] === undefined) return;

      if (!this.$data._isSelect && !this.$data._isAutocomplete && !this.$data._isDatepicker) {
        this.$nextTick(() => this.$refs[this.$data._elementRef].select())
      } else {
        this.$nextTick(() => this.$refs[this.$data._elementRef].focus())
      }
    },

    checkHtml5Validity() {
      if (this.$refs[this.$data._elementRef] === undefined) return;

      const el = this.$data._isAutocomplete || this.$data._isDatepicker
        ? this.$refs.input.$refs.input
        : this.$refs[this.$data._elementRef];

      let type = null;
      let message = null;
      let isValid = true;
      if (!el.checkValidity()) {
        type = 'is-danger';
        message = el.validationMessage;
        isValid = false;
      }
      this.isValid = isValid;

      if (this.parentField) {
        // Set type only if not defined
        if (!this.parentField.type) {
          this.parentField.newType = type;
        }
        // Set message only if not defined
        if (!this.parentField.message) {
          this.parentField.newMessage = message;
        }
      }

      return this.isValid;
    }
  }
}
