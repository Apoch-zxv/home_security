__author__ = 'grg'

import select
import socket
import sys
import logging

logger = logging.getLogger("home_security")
# create console handler with a higher log level
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
# create formatter and add it to the handlers
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch.setFormatter(formatter)
logger.setLevel(logging.DEBUG)
logger.addHandler(ch)

class Runner(object):
    def __init__(self, port, max_clients = 20, host = ""):
        self._port = port
        self._host = host
        self._max_clients = max_clients
        self._server = None
        self._is_stop = False
        self._logger = logging.getLogger("home_security")

    def start(self):
        self._server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._server.bind((self._host, self._port))
        self._server.listen(self._max_clients)

        self._logger.info("Starting server on " + str((self._host, self._port)))

        listen_sockets = [self._server]
        while not self._is_stop:
            try:
                input_ready, output_ready, except_ready = select.select(listen_sockets, [], [])

                for input_socket in input_ready:
                    if self._server == input_socket:
                        self._handle_new_connection(input_socket, listen_sockets)
                    else:
                        self._handle_request(input_socket, listen_sockets)
            except:
                self._logger.error("Got exception")

    def stop(self):
        self._server.close()

    def _handle_new_connection(self, input_socket, listen_sockets):
        connection, client_address = input_socket.accept()
        self._logger.info("Received new connection " + str(client_address))
        listen_sockets.append(connection)

    def _handle_request(self, input_socket, listen_sockets):
        data = input_socket.recv(4096 * 1024)
        if data:
            self._logger.info("Recieved data: " + data)
        else:
            listen_sockets.remove(input_socket)
            self._logger.error("Disconnecting")

runner = Runner(5000)
runner.start()