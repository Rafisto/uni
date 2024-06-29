import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import javax.management.RuntimeErrorException;

public class PascalRowInvoker {
    public static List<Integer> InvokeRow(int row) throws RuntimeErrorException {
        try {
            List<String> command = new ArrayList<>();
            command.add("./app.out");
            command.add(String.valueOf(row));
            for (int i = 0; i <= row; i++) {
                command.add(String.valueOf(i));
            }

            AppLogger.logger.info("[IN] Invoking " + command.toString());

            ProcessBuilder processBuilder = new ProcessBuilder(command);
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            List<Integer> resultList = new ArrayList<>();
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("-->");
                if (parts.length == 2) {
                    int number = Integer.parseInt(parts[1].trim());
                    resultList.add(number);
                }
            }
            process.waitFor();
            AppLogger.logger.info("[OUT] Received "+resultList.toString());
            return resultList;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        throw new RuntimeErrorException(null, "The process has not finished properly");
    }
}
