package it.unibo.mvc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ConfigFileParser {

    private final Map<String, String> parsedConfig;

    /**
     * Create a wrapper for the configuration file.
     * @param configPath path to the configuration file
     */
    public ConfigFileParser(final String configPath) {
        this.parsedConfig = new HashMap<>();
        try {
            final List<String> lines = Files.readAllLines(Path.of(configPath));
            lines.forEach(s -> {
                final String[] tokens = s.split(": ");
                this.parsedConfig.put(tokens[0], tokens[1]);
            });
        } catch (IOException e) {
            System.out.println(e); // NOPDM: exercise
            System.exit(0);
        }
    }

    /**
     * @param key that identifies that data
     * @return data associated with key
     */
    public String get(final String key) {
        return this.parsedConfig.get(key);
    }
}
 