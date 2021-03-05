<template>
  <div class="dialog modal is-active" v-if="isActive">
    <div class="modal-background" :class="[{'background-drag': disableClickOutside}]" @click="cancel('outside')"></div>
    <div class="modal-card animation-content">
      <header class="modal-card-head" v-if="title">
        <p class="modal-card-title">{{ title }}</p>
      </header>

      <section
        class="modal-card-body"
        :class="{ 'is-titleless': !title, 'is-flex': hasIcon }">
        <div class="media">
          <div class="media-left" v-if="hasIcon">
            <v-icon
              :icon="icon ? icon : iconByType"
              :pack="iconPack"
              :type="type"
              :both="!icon"
              size="is-large">
            </v-icon>
          </div>
          <div class="media-content">
            <p v-html="message"></p>
          <div v-if="hasInput" class="field">
            <div class="control">
              <input v-model="prompt"
                class="input"
                ref="input"
                :required="required"
                :class="{ 'is-danger': validationMessage }"
                v-bind="inputAttrs"
                @keyup.enter="confirm">
            </div>
              <p class="help is-danger">{{ validationMessage }}</p>
            </div>
          </div>
        </div>
      </section>

      <footer class="modal-card-foot">
        <button
          v-if="showCancel"
          class="button is-light"
          ref="cancelButton"
          @click="cancel('button')">
          {{ cancelText }}
        </button>
        <button
          class="button"
          :class="type"
          ref="confirmButton"
          @click="confirm">
          {{ confirmText }}
        </button>
      </footer>
    </div>
  </div>
</template>

<script>
import Icon from '../icon';
import config from '../../utils/config';
export default {
  name: 'vDialog',
  components: {
    [Icon.name]: Icon
  },
  props: {
    title: String,
    message: String,
    icon: String,
    iconPack: String,
    hasIcon: Boolean,
    disableClickOutside:false, //禁止点击外部取消响应
    type: {
      type: String,
      default: 'is-primary'
    },
    confirmText: {
      type: String,
      default: () => {
        return config.defaultDialogConfirmText
          ? config.defaultDialogConfirmText
          : 'OK';
      }
    },
    cancelText: {
      type: String,
      default: () => {
        return config.defaultDialogCancelText
          ? config.defaultDialogCancelText
          : 'Cancel';
      }
    },
    hasInput: Boolean, // Used internally to know if it's prompt
    inputAttrs: {
      type: Object,
      default: () => {}
    },
    onConfirm: {
      type: Function,
      default: () => {}
    },
    onCancel: {
      type: Function,
      default: () => {}
    },
    onClickOutside: {
      type: Function,
      default: () => {}
    },
    canCancel: {
      type: [Array, Boolean],
      default: () => ['escape', 'x', 'outside', 'button']
    },
    required: true
  },
  data() {
    const prompt = this.hasInput ? this.inputAttrs.value || '' : '';
    return {
      prompt,
      isActive: false,
      validationMessage: ''
    };
  },
  computed: {
    /**
     * Icon name (MDI) based on the type.
     */
    iconByType() {
      switch (this.type) {
        case 'is-info':
          return 'information';
        case 'is-success':
          return 'check-circle';
        case 'is-warning':
          return 'alert';
        case 'is-danger':
          return 'alert-circle';
        default:
          return null;
      }
    },
    cancelOptions() {
      return typeof this.canCancel === 'boolean'
        ? this.canCancel ? ['escape', 'x', 'outside', 'button'] : []
        : this.canCancel;
    },
    showCancel() {
      return this.cancelOptions.indexOf('button') >= 0;
    }
  },
  watch: {
    isActive() {
      if (typeof window !== 'undefined') {
        const action = this.isActive ? 'add' : 'remove';
        document.documentElement.classList[action]('is-clipped');
      }
    }
  },
  methods: {
    /**
     * If it's a prompt Dialog, validate the input.
     * Call the onConfirm prop (function) and close the Dialog.
     */
    confirm() {
      if (this.$refs.input !== undefined) {
        if (!this.$refs.input.checkValidity()||(this.required&&this.prompt.trim()==='')) {
          this.validationMessage = this.$refs.input.validationMessage||'请填写此字段。';
          this.$nextTick(() => this.$refs.input.select());
          return;
        }
      }
      this.onConfirm(this.prompt);
      this.close();
    },
    cancel(method) {
      if (this.cancelOptions.indexOf(method) < 0||(this.disableClickOutside&&method ==='outside')) return;
      this.onCancel.apply(null, arguments);
      this.onClickOutside.apply(null, arguments);
      this.close();
    },
    /**
     * Close the Dialog.
     */
    close() {
      this.isActive = false;
      // this.onCancel.apply(null, arguments);
      // Timeout for the animation complete before destroying
      setTimeout(() => {
        this.$destroy();
        // removeElement(this.$el);
        if (typeof this.$el.remove !== 'undefined') {
          this.$el.remove();
        } else {
          this.$el.parentNode.removeChild(this.$el);
        }
      }, 150);
    }
  },
  beforeMount() {
    // Insert the Dialog component in body tag
    document.body.appendChild(this.$el);
  },
  mounted() {
    this.isActive = true;
    this.$nextTick(() => {
      // Handle which element receives focus
      this.hasInput
        ? this.$refs.input.focus()
        : this.$refs.confirmButton.focus();
    });
  }
};
</script>
