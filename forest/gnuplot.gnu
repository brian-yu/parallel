set terminal png
set output "fire.png"
plot "data.txt" u 1:2 w l notitle
