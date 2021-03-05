<template>
    <div class="control"
        :class="{ 'is-expanded': expanded, 'has-icons-left': icon }">
        <span class="select"
            :class="[size, statusType, {
                'is-fullwidth': expanded,
                'is-loading': loading,
                'is-empty': selected === null
            }]">

            <select v-model="selected"
                class='selectsss'
                ref="select"
                :class="isBorder?'':'select-border'"
                :disabled="disabled"
                :readonly="readonly"
                :name="name"
                :size ="size"
                style="height:200"
                :required="required"
                @focus="$emit('focus', $event)"
                @blur="$emit('blur', $event)">

                <option
                    v-if="placeholder"
                    :value="null"
                    selected
                    disabled
                    hidden>
                    {{ placeholder }}
                </option>
                <slot></slot>

            </select>
        </span>
    </div>
</template>

<script>
import FormElementMixin from '../../utils/FormElementMixin';

export default {
  name: 'vSelect',
  mixins: [FormElementMixin],
  props: {
    value: {
      type: [String, Number, Boolean, Object, Array, Symbol, Function],
      default: null
    },
    isBorder: Boolean,
    size: {
      type:[String, Number],
      default: 0
    }
  },
  data() {
    return {
      selected: this.value,
      _elementRef: 'select'
    };
  },
  watch: {
    value(value) {
      this.selected = value;
      !this.isValid && this.checkHtml5Validity();
    },

    selected(value) {
      this.$emit('input', value);
      this.$emit('change', value);
      !this.isValid && this.checkHtml5Validity();
    }
  },
  methods: {
    blur(event) {
      this.$emit('blur', event);
      this.checkHtml5Validity();
    }
  }
};
</script>
<style lang="scss" scoped>
.select {
  height: 100%;
  select {
    height: 100%;
    border-radius: $--border-radius-none !important;
  }
}
.select-border {
  border: 0px !important;
  box-shadow: none;
  border-bottom: 1px solid $--border-color-blue !important;
}
</style>