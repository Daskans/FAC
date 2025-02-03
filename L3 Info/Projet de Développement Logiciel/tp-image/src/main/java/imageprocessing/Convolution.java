package imageprocessing;

import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayS16;
import boofcv.struct.image.GrayU8;


public class Convolution {

  public static void meanFilter(GrayU8 input, GrayU8 output, int size) {
    double[][] convCore = new double[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            convCore[j][i] = 1/(size*size);
        }
    }
    for (int y = 1; y < input.height - 1; ++y) {
        for (int x = 1; x < input.width - 1; ++x) {
            double gl = 0;
            for(int j = y-1; j < y+2; j++) {
                for(int i = x-1; i < x+2; i++) {
                    System.out.println(" input.get(i, j): " + input.get(i, j) + " convCore[j-y+1][i-x+1]: " + convCore[j-y+1][i-x+1]);
                    gl += input.get(i, j)*convCore[j-y+1][i-x+1];
                    System.out.println("gl : " + gl);
                }
            }
            output.set(x, y, ((int)gl));
        }
    }
  }

  public static void convolution(GrayU8 input, GrayS16 output, int[][] kernel) {
      // TODO
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
    meanFilter(input, output, 3);
    
    // save output image
    final String outputPath = args[1];
    UtilImageIO.saveImage(output, outputPath);
    System.out.println("Image saved in: " + outputPath);
  }

}
