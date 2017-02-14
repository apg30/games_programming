

Cell::calculate_g()
{
  g = g + 10;
}
Cell::calculate_h()
{
  abs();
}
Cell::calculate_f()
{

}

float Cell::man_distance(Cell cell){

  float diff_x = (float)(abs(this->x - cell.x));
  float diff_y = (float)(abs(this->y - cell.y));

		return diff_x + diff_y;
}

bool Cell::operator!=(Cell cell){
	if (x == cell.x && y == cell.y)
	{
		return false;
	}
	else
	{
		return true;
	}
