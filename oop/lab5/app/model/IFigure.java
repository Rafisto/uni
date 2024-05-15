package app.model;

import java.io.Serializable;

/**
 * The IFigure interface represents a figure in a graphical application.
 * It extends the IFigurePhysics and IFigureGUI interfaces and implements the Serializable interface.
 * 
 * <p>
 * This interface provides a common contract for all figures in the application.
 * Figures that implement this interface can be used for physics calculations and GUI rendering.
 * </p>
 */
public interface IFigure extends IFigurePhysics, IFigureGUI, Serializable {
}