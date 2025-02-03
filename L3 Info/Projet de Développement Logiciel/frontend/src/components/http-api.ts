import { ref } from 'vue'
import axios from 'axios';


interface Image_t {
    id: number;
    name: string;
}

const images = ref(<Image_t[]>([]));
const imageElement = ref<HTMLImageElement | null>(null);
export const selectedImage = ref("");

const downloadImage = async (id:number) => {
    var imageUrl;
    if (id != -1) {
        imageUrl = `/images/${id}`;
    } else {
        imageUrl = `/images/${selectedImage.value}`;
    }
    console.log("Image URL => ",imageUrl);
    console.log("Image ID => ",selectedImage.value);
    console.log("Image element => ",imageElement);
    console.log("Image element value => ",imageElement.value);
    console.log("Image element value src => ",imageElement.value?.src);
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
      return response;
    } catch (error) {
      console.error(error);
    }
  }

const getImageList = async () => {
  try {
    const response = await axios.get('/images');
    images.value = response.data;
    console.log(images.value);
    if (images.value != undefined) {
        return images;
    }
  } catch (error) {
    console.error(error);
  }
}

export { images, getImageList, imageElement, downloadImage };
export type { Image_t };