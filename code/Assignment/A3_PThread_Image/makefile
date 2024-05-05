CC = g++
CFLAGS = -lpthread
TARGET = a.out

.PHONY: all clean

all: apply_blur apply_edge apply_sharp papply_blur papply_edge papply_sharp

apply_blur:
	$(CC) $(CFLAGS) A1_apply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt K1_blur.txt output.txt

apply_edge:
	$(CC) $(CFLAGS) A1_apply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt K2_Edge_Detection.txt output.txt

apply_sharp:
	$(CC) $(CFLAGS) A1_apply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt K3_Sharpen.txt output.txt

papply_blur:
	$(CC) $(CFLAGS) A2_papply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt K1_blur.txt output.txt 8

papply_edge:
	$(CC) $(CFLAGS) A2_papply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt K2_Edge_Detection.txt output.txt 8

papply_sharp:
	$(CC) $(CFLAGS) A2_papply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt K3_Sharpen.txt output.txt 8

clean:
	rm -f $(TARGET) output.txt
