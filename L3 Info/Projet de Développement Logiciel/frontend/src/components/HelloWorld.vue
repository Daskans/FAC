<script setup lang="ts">
import { ref } from 'vue'
import axios from 'axios';

interface Image {
  id: number;
  name: string;
}

defineProps<{ msg: string }>()
const images = ref(<Image[]>([]));
const selectedImage = ref("");
const imageElement = ref<HTMLImageElement | null>(null);


const getImageList = async () => {
  try {
    const response = await axios.get('/images');
    images.value = response.data;
    console.log(images.value);
  } catch (error) {
    console.error(error);
  }
}

const downloadImage = async (imageId: number) => {
  
  try {
    const response = await axios.get(`/images/${selectedImage.value}`, { responseType: 'blob' });
    const reader = new window.FileReader();
    reader.readAsDataURL(response.data);
    reader.onload = function() {

    }
  } catch (error) {
    console.error(error);
  }
}
</script>

<template>
  <h1>{{ msg }}</h1>

  <button @click="getImageList()">lézimaj</button>
  <div>
    <select>
      <option v-for="image in images" :key="image.id" :value="image.id">
        {{ image.name }}
      </option>
    </select>
  </div>
</template>

<style scoped>
.read-the-docs {
  color: #414040;
}

button {
  background-color: #9499be;
  color: white;
  padding: 10px 20px;
  border-radius: 5px;
  cursor: pointer;
}

select {
  margin-top: 20px;
}
</style>
