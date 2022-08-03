import json
import os
from typing import Dict, List, Tuple
from aiohttp import web

from sound_laser.speaker import SpeakerControl


class Server:
    """Basic Server with API interfaces and a website to control the speaker
    """

    def __init__(self, port=80, web_directory: str = "./www") -> None:
        """Basic Server with API interfaces and a website to control the speaker

        Args:
            port (int, optional): Port on wich the server will listen. Defaults to 80.
            web_directory (str, optional): Directory wich includes the html, css and js files for the website. Defaults to "./www".
        """

        self.port = port
        self.server = web.Application()
        self._web_directory = web_directory

    def open(self):
        """Run the server
        """

        self._webserver = Webserver(self.server, self._web_directory)
        self._api = API(self.server)
        web.run_app(self.server, port=self.port)


class Webserver:
    """Webserver wich provides all files in a drectory over different routes
    """

    def __init__(self, server: web.Application, web_directory: str) -> None:
        """Webserver wich provides all files in a drectory over different routes

        Args:
            server (web.Application): aiohttp Application reference
            web_directory (str): Directory wich includes the files
        """

        self.server = server
        self.web_path = web_directory
        self._create_webserver()

    async def _webadress_handler(self, req: web.Request):
        """Handle the requests of any file

        Returns:
            web.Response: HTTP response with the requested file
        """

        path = req.path.lstrip("/")
        route_config = self.web_routes[path]
        with open(os.path.join(self.web_path, route_config[0])) as f:
            return web.Response(text=f.read(), content_type=route_config[1])

    def _create_routes(self, files: List[str]) -> Dict[str, Tuple[str, str]]:
        """Create Routes from a set of filenames

        Args:
            files (List[str]): filenames in a list

        Returns:
            Dict[str, Tuple(str, str)]: Filename and content type organised by route
        """

        routes = {}
        for file in files:
            route = file

            split_file = os.path.splitext(file)
            content_type = f"text/{split_file[1].lstrip('.')}"

            if split_file[1] == ".html":
                if split_file[0] == "index":
                    route = ""
                else:
                    route = f"{split_file[0]}"
            if split_file[1] == ".js":
                content_type == f"text/javascript"

            routes[route] = (file, content_type)

        print(routes)

        return routes

    def _create_webserver(self):
        """Check content in the web directory and register routes depending on the files in this directory
        """

        files = os.listdir(self.web_path)
        routes = self._create_routes(files)

        for route in routes:
            self.server.router.add_get(f"/{route}", self._webadress_handler)

        self.web_routes = routes


class API:
    """REST API for different Usecases
    """

    def __init__(self, server: web.Application) -> None:
        self.server = server
        self._create_api()

    async def _tilt_x_handler(self, req: web.Request):
        """Handle tilting request around the x axis

        Returns:
            web.Response: HTTP response with success flag in JSON format
        """

        try:
            content = json.loads(await req.text())
            angle = content["value"]
            print(angle)
            self.speaker_control.tilt_x(angle)

            res = dict(success=True, message="")
        except Exception as err:
            res = dict(success=True, message=getattr(
                err, "message", repr(err)))

        return web.Response(text=json.dumps(res), content_type='application/json')

    async def _tilt_y_handler(self, req: web.Request):
        """Handle tilting request around the y axis

        Returns:
            web.Response: HTTP response with success flag
        """
        try:
            content = json.loads(await req.text())
            angle = content["value"]
            print(angle)
            self.speaker_control.tilt_y(angle)

            res = dict(success=True, message="")
        except Exception as err:
            res = dict(success=True, message=getattr(
                err, "message", repr(err)))

        return web.Response(text=json.dumps(res), content_type='application/json')

    async def _get_tilt_handler(self, req: web.Request):
        """Handle request about the speaker position

        Returns:
            web.Response: HTTP response with x and y tilting angle in JSON format
        """

        return web.Response(
            text=json.dumps(dict(
                x=self.speaker_control.x_angle,
                y=self.speaker_control.y_angle
            )), content_type='application/json')

    def _create_api(self):
        """Register different routes for the API
        """

        self.speaker_control = SpeakerControl(12, 13)
        self.server.router.add_post("/tilt/x", self._tilt_x_handler)
        self.server.router.add_post("/tilt/y", self._tilt_y_handler)
        self.server.router.add_get("/tilt", self._get_tilt_handler)
