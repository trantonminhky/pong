bool isWithinX(int curX, int windowSizeX) {
	return (curX >= 0 && curX <= windowSizeX - 20); // accounts for rectangle size
}