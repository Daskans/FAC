package pdl.backend;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import javax.print.attribute.standard.Media;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.ObjectNode;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.InputStreamResource;
import org.springframework.http.HttpStatus;
import org.springframework.http.HttpStatusCode;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@RestController
public class ImageController {

  @Autowired
  private ObjectMapper mapper;

  private final ImageDao imageDao;

  @Autowired
  public ImageController(ImageDao imageDao) {
    this.imageDao = imageDao;
  }

  @RequestMapping(value = "/images/{id}", method = RequestMethod.GET, produces = MediaType.IMAGE_JPEG_VALUE)
  public ResponseEntity<?> getImage(@PathVariable("id") long id) {
        Optional<Image> img = imageDao.retrieve(id);
        if (img.isEmpty()) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        return ResponseEntity
            .ok()
            .contentType(MediaType.IMAGE_JPEG)
            .body(img.get().getData());
  }

    @RequestMapping(value = "/images/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<?> deleteImage(@PathVariable("id") long id) {
        Optional<Image> img = imageDao.retrieve(id);
        if (img.isEmpty()) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        imageDao.delete(img.get());
        return ResponseEntity
            .ok()
            .contentType(MediaType.IMAGE_JPEG)
            .body(img.get().getData());
  }

    @RequestMapping(value = "/images", method = RequestMethod.POST)
    public ResponseEntity<?> addImage(@RequestParam("file") MultipartFile file, RedirectAttributes redirectAttributes) {

        if (!(file.getContentType().equals(MediaType.IMAGE_JPEG_VALUE))) {
            return new ResponseEntity<>(HttpStatus.UNSUPPORTED_MEDIA_TYPE);
        }
        
        Optional<Image> img;
        try {
            img = Optional.of(new Image(file.getOriginalFilename(), file.getBytes()));
        } catch (final IOException e) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        imageDao.create(img.get());
        redirectAttributes
            .addAttribute("id", img.get().getId())
            .addAttribute("name", img.get().getName())
            .addAttribute("data", img.get().getData());
        return ResponseEntity
            .ok()
            .contentType(MediaType.IMAGE_JPEG)
            .body(img.get().getData());
    }

    @RequestMapping(value = "/images", method = RequestMethod.GET, produces = "application/json; charset=UTF-8")
    @ResponseBody
    public ArrayNode getImageList() {
        ArrayNode nodes = mapper.createArrayNode();
        List<Image> images = imageDao.retrieveAll();
        for (Image img : images) {
            ObjectNode obj = mapper.createObjectNode();
            obj.put("id", img.getId());
            obj.put("name", img.getName());
            nodes.add(obj);
        }
        return nodes;
    }

}
