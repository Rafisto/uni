package app.logger;

import java.io.IOException;
import java.util.logging.*;

/**
 * The AppLogger class provides logging functionality for the application.
 * It configures the logger to log messages to the console and a file.
 * This class cannot be instantiated as it is a full static class.
 */
public final class AppLogger
{
    
    private AppLogger()
    {
        throw new InstantiationError("AppLogger is a full statc class");
    }

    public static final Logger logger = Logger.getGlobal();
    
    /**
     * Configures the logger for the application.
     * This method removes any existing handlers from the logger, sets the log format,
     * adds a console handler with INFO level, and adds a file handler with ALL level.
     * If the file handler cannot be created, a warning message is logged.
     */
    public final static void ConfigureLogger()
    {
        Handler[] handlers = logger.getHandlers();
        for(Handler handler : handlers)
            logger.removeHandler(handler);

        logger.setUseParentHandlers(false);
        
        System.setProperty("java.util.logging.SimpleFormatter.format", 
        "%1$tF %1$tT %4$s %2$s %5$s%6$s%n");

        ConsoleHandler ch = new ConsoleHandler();
        ch.setLevel(Level.WARNING);
        logger.addHandler(ch);

        try
        {
            FileHandler fh = new FileHandler("./log.txt");
            fh.setLevel(Level.ALL);
            fh.setFormatter(new SimpleFormatter());
            logger.addHandler(fh);
        }
        catch (IOException | SecurityException e)
        {
            logger.warning("Unable to load output file 'log.txt'");
        }

        logger.setLevel(Level.ALL);
    }
}