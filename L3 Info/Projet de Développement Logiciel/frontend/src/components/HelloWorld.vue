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
const selectedFile = ref<File | null>(null);
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

const downloadImage = async () => {
  const imageUrl = `/images/${selectedImage.value}`;
  console.log("Image URL => ",imageUrl);
  console.log("Image ID => ",selectedImage.value);
  console.log("Image element => ",imageElement.value);
  try {
    const response = await axios.get(imageUrl, { responseType: 'blob' });
    const reader = new window.FileReader();
    reader.readAsDataURL(response.data);
    reader.onload = function() {
      const imageUrl = reader.result;
      if (imageElement.value && imageUrl) {
        imageElement.value.src = imageUrl.toString();
      }
    }
  } catch (error) {
    console.error(error);
  }
}

const submitFile = async () => {
  if (selectedFile.value) {
    const formData = new FormData();
    formData.append('file', selectedFile.value);
    try {
      const response = await axios.post('/images', formData, {
        headers: {
          'Content-Type': 'multipart/form-data'
        }
      });
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  }
}

const handleFileUpload = (event: Event) => {
  const target = event.target as HTMLInputElement;
  if (target.files && target.files.length > 0) {
    selectedFile.value = target.files[0];
  }
}

</script>

<template>
  <h1>{{ msg }}</h1>

  <button @click="getImageList()">lézimaj</button>
  <div>
    <select v-model = "selectedImage">
      <option v-for="image in images" :key="image.id" :value="image.id">
        {{ image.name }}
      </option>
    </select>
  </div>
  <div>
    <button @click="downloadImage()">Download</button>
  </div>
  <div class = "imageContainer">
    <img ref="imageElement" class = "mainImage" />
  </div>
  <div class="container">
    <div>
      <h2>Single File</h2>
      <hr/>
      <label>File
        <input type="file" @change="handleFileUpload"/>
      </label>
      <br>
      <button v-on:click="submitFile()">Submit</button>
    </div>
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

.imageContainer {
  margin-top: 20px;
}

.mainImage {
  max-width: 100%;
  height: auto;
}

.container {
  margin-top: 20px;
  display: flex;
  gap: 10px;
  align-items: center;
  justify-content: center;
}

input[type="file"] {
  padding: 10px;
}

</style>
