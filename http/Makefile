# Define variables
PROJECT_ROOT=$(shell cd ..; pwd)
CONF_FILE=conf.txt
LD_LIBRARY_PATH=../libparser:../librequest-0.5

# Build the server
all: server conf

server:
	@echo "Compiling server..."
	@$(CC) -I ../libparser -I ../librequest-0.5/api -L ../libparser -L ../librequest-0.5 -o server server.c -lparser -lrequest -lm
	@echo "Server compiled successfully."

# Generate the conf.txt file dynamically
conf:
	@echo "Generating $(CONF_FILE)..."
	@echo "http://127.0.0.1" >> $(CONF_FILE)
	@echo "$(PROJECT_ROOT)/site1/" >> $(CONF_FILE)
	@echo "http://127.0.0.2" >> $(CONF_FILE)
	@echo "$(PROJECT_ROOT)/site2/" >> $(CONF_FILE)
	@echo "http://127.0.0.3" >> $(CONF_FILE)
	@echo "$(PROJECT_ROOT)/site3/" >> $(CONF_FILE)
	@echo "$(CONF_FILE) generated successfully."

# Run the server with the appropriate LD_LIBRARY_PATH
run: server
	@echo "Running server..."
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./server

# Clean up generated files
clean:
	@rm -f server $(CONF_FILE)
	@echo "Cleaned up all generated files."
