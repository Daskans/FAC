package imageprocessing;

import boofcv.core.image.ConvertImage;
import boofcv.io.image.ConvertBufferedImage;
import boofcv.io.image.UtilImageIO;
import boofcv.struct.image.GrayS16;
import boofcv.struct.image.GrayU8;
import boofcv.struct.image.Planar;
import java.awt.image.BufferedImage;
import boofcv.alg.color.ColorHsv;

public class Convolution {

    public static void meanFilter(Planar<GrayU8> input, Planar<GrayU8> output, int size) {
        for (int band = 0; band < input.getNumBands(); ++band) {
            for (int y = size / 2; y < input.height - (size / 2); ++y) {
                for (int x = size / 2; x < input.width - (size / 2); ++x) {
                    int color = 0;
                    for (int j = y - (size / 2); j < y + (size / 2) + 1; j++) {
                        for (int i = x - (size / 2); i < x + (size / 2) + 1; i++) {
                            color += input.getBand(band).get(i, j);
                        }
                    }
                    output.getBand(band).set(x, y, (color / (size * size)));
                }
            }
        }
    }

    public static void grayScaledImage(Planar<GrayU8> input, Planar<GrayU8> output) {
        float[] coef = {0.3f, 0.59f, 0.11f};
        for (int y = 0; y < input.height; ++y) {
            for (int x = 0; x < input.width; ++x) {
                int color = 0;
                for (int band = 0; band < input.getNumBands(); ++band) {
                    color += input.getBand(band).get(x, y) * coef[band];
                }
                for (int band = 0; band < input.getNumBands(); ++band) {
                    output.getBand(band).set(x, y, color);
                }
            }
        }
    }

    public static void convolution(Planar<GrayU8> input, Planar<GrayS16> output, int[][] kernel) {
        int n_height = kernel.length / 2;
        int n_width = kernel[0].length / 2;
        for (int band = 0; band < input.getNumBands(); ++band) {
            for (int y = n_height; y < input.height - n_height; ++y) {
                for (int x = n_width; x < input.width - n_width; ++x) {
                    int color = 0;
                    for (int u = -n_height; u <= n_height; u++) {
                        for (int v = -n_width; v <= n_width; v++) {
                            color += input.getBand(band).get(x + u, y + v) * kernel[u + n_height][v + n_width];
                        }
                    }
                    output.getBand(band).set(x, y, color);
                }
            }
        }
    }

    public static void gradientImage(GrayU8 input, GrayU8 output, int[][] kernelX, int[][] kernelY) {
        int n = kernelX.length / 2;
        for (int y = n; y < input.height - n; ++y) {
            for (int x = n; x < input.width - n; ++x) {
                int gx = 0;
                int gy = 0;
                int gl = 0;
                for (int u = -n; u <= n; u++) {
                    for (int v = -n; v <= n; v++) {
                        gx += input.get(x + u, y + v) * kernelX[u + n][v + n];
                        gy += input.get(x + u, y + v) * kernelY[u + n][v + n];
                    }
                }
                gl = (int) Math.sqrt(gx * gx + gy * gy);
                output.set(x, y, gl);
            }
        }
    }

    public static void gradientImageSobel(GrayU8 input, GrayU8 output) {
        int[][] kernelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
        int[][] kernelY = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
        gradientImage(input, output, kernelX, kernelY);
    }

    public static void gradientImagePrewitt(GrayU8 input, GrayU8 output) {
        int[][] kernelX = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
        int[][] kernelY = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
        gradientImage(input, output, kernelX, kernelY);
    }
    public static void main(final String[] args) {
        // load image
        if (args.length < 2) {
            System.out.println("missing input or output image filename");
            System.exit(-1);
        }
        final String inputPath = args[0];
        //GrayU8 input = UtilImageIO.loadImage(inputPath, GrayU8.class);
        //GrayU8 output = input.createSameShape();
        BufferedImage input = UtilImageIO.loadImage(inputPath);
        Planar<GrayU8> image = ConvertBufferedImage.convertFromPlanar(input, null, true, GrayU8.class);
        Planar<GrayU8> output = new Planar<>(GrayU8.class, image.width, image.height, image.getNumBands());
        //Planar<GrayS16> outputS16 = new Planar<>(GrayS16.class, image.width, image.height, image.getNumBands());
        //int[][] Neg = {{-1}};
        // processing
        //meanFilter(image, output, 11);
        grayScaledImage(image, output);
        //convolution(image, outputS16, (int[][]) Neg);
        //output = ConvertImage.convert(outputS16, (GrayU8) null);
        //gradientImageSobel(input, output);
        //gradientImagePrewitt(input, output);

        // save output image
        final String outputPath = args[1];
        UtilImageIO.saveImage(output, outputPath);
        System.out.println("Image saved in: " + outputPath);
    }
}
