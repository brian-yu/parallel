double shadow = 40% * ambient + 60% * light * dotproduct;

double reflection = P * original + (1 - P) * reflective;

/*
R - 2(N•R)N


for the checkerboard, base it on the x and z coordinaets of the point of intersection
*/

