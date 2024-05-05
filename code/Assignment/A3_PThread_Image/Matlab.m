A = dlmread('output.txt');
A(1, :) = [];
figure; imshow(A, [0, 255]);