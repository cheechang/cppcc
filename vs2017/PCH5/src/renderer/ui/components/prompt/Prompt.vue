<template>
  <div class="prompt">
    <div class="modal-background" @click="$emit('close')"></div>
    <transition name="fade">
      <article v-if="isActive" class="message" :class="[type, size]">
        <header v-if="title" class="message-header">
          <p>{{ title }}</p>
          <button v-if="closable" type="button" class="delete" @click="$emit('close')"></button>
        </header>
        <section class="message-body">
          <div class="media">
            <div v-if="icon && hasIcon" class="media-left">
                <v-icon :icon="icon"
                  :class="type"
                  both
                  size="is-large">
                </v-icon>
            </div>
            <div class="media-content">
              <slot></slot>
            </div>
          </div>
        </section>
      </article>
    </transition>
  </div>
</template>

<script>
import PromptMixin from '../../utils/PromptMixin.js';

export default {
  name: 'vPrompt',
  mixins: [PromptMixin]
};
</script>
