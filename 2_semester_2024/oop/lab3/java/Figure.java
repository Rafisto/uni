/*
 * An abstract Figure class, which has an area, perimeter and a name
 */
public abstract class Figure implements FigureInterface {
    /*
     * Each figure has an area
     */
    @Override
    public abstract double area();
    /*
     * Each figure has a perimeter
     */ 
    @Override
    public abstract double perimeter();
    
    /*
     * Each figure object has a name
     */
    public abstract String name();
}