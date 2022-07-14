from email import message
from json import JSONEncoder
import json
import os
from aiohttp import web

BASE_PATH = os.path.abspath(os.path.dirname(__file__))


class Server:
    def __init__(self, port=80) -> None:
        self.port = port
        self.server = web.Application()

    async def _tilt_x_handler(self, req: web.Request):
        try:
            content = json.loads(await req.text())
            print(content["value"])

            res = dict(success=True, message="")
        except Exception as err:
            res = dict(success=True, message=getattr(
                err, "message", repr(err)))

        return web.Response(text=json.dumps(res), content_type='text/json')

    async def _tilt_y_handler(self, req: web.Request):
        try:
            content = json.loads(await req.text())
            print(content["value"])

            res = dict(success=True, message="")
        except Exception as err:
            res = dict(success=True, message=getattr(
                err, "message", repr(err)))

        return web.Response(text=json.dumps(res), content_type='text/json')

    def _create_api(self):
        self.server.router.add_post("/tilt/x", self._tilt_x_handler)
        self.server.router.add_post("/tilt/y", self._tilt_y_handler)

    def _webadress_handler(self, req: web.Request):
        path = req.path.lstrip("/")
        file = self.web_routes[path]
        with open(os.path.join(self.web_path, file)) as f:
            return web.Response(text=f.read(), content_type='text/html')

    def _create_webserver(self):
        self.web_path = os.path.join(os.path.dirname(BASE_PATH), "www")
        files = os.listdir(self.web_path)
        routes = {"" if f[1] == "index" else f[1]: f[0] for f in map(
            lambda file_name: (file_name, os.path.splitext(file_name)[0]), files)}

        for route in routes:
            self.server.router.add_get(f"/{route}", self._webadress_handler)

        self.web_routes = routes

    def open(self):
        self._create_api()
        self._create_webserver()
        web.run_app(self.server, port=self.port)


if __name__ == "__main__":
    server = Server(8080)
    server.open()
