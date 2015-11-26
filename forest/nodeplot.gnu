set terminal png
set output "nodes.png"
plot "nodes.txt" u 1:2 w l notitle
