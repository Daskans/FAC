package imageprocessing;

import boofcv.core.image.ConvertImage;
import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayS16;
import boofcv.struct.image.GrayU8;


public class Convolution {

  public static void meanFilter(GrayU8 input, GrayU8 output, int size) {
    for (int y = size/2; y < input.height - (size/2); ++y) {
        for (int x = size/2; x < input.width - (size/2); ++x) {
            int gl = 0;
            for(int j = y-(size/2); j < y+(size/2)+1; j++) {
                for(int i = x-(size/2); i < x+(size/2)+1; i++) {
                    gl += input.get(i, j);
                }
            }
            output.set(x, y, (gl/(size*size)));
        }
    }
  }

  public static void convolution(GrayU8 input, GrayS16 output, int[][] kernel) {
    ConvertImage.conv
  }

  public static void gradientImage(GrayU8 input, GrayU8 output, int[][] kernelX, int[][] kernelY){
      // TODO
  }

  public static void gradientImageSobel(GrayU8 input, GrayU8 output){
    int[][] kernelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int[][] kernelY = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    gradientImage(input, output, kernelX, kernelY);
  }

  public static void gradientImagePrewitt(GrayU8 input, GrayU8 output){
      // TODO
  }

  
  public static void main(final String[] args) {
    // load image
    if (args.length < 2) {
      System.out.println("missing input or output image filename");
      System.exit(-1);
    }
    final String inputPath = args[0];
    GrayU8 input = UtilImageIO.loadImage(inputPath, GrayU8.class);
    GrayU8 output = input.createSameShape();

    // processing
    //meanFilter(input, output, 11);
    convolution(input, , kernelX);
    
    // save output image
    final String outputPath = args[1];
    UtilImageIO.saveImage(output, outputPath);
    System.out.println("Image saved in: " + outputPath);
  }

}
