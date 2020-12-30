export const PROJECT_NAME = process.env.REACT_APP_PROJECT_NAME!;
export const PROJECT_PATH = process.env.REACT_APP_PROJECT_PATH!;

export const ENDPOINT_ROOT = calculateEndpointRoot("/rest/");
export const WEB_SOCKET_ROOT = calculateWebSocketRoot("/ws/");

function calculateEndpointRoot(endpointPath: string) {
    const httpRoot = process.env.REACT_APP_HTTP_ROOT;
    if (httpRoot) {
        return httpRoot + endpointPath;
    }
    const location = window.location;
    return location.protocol + "//" + location.host + endpointPath;
}

function calculateWebSocketRoot(webSocketPath: string) {
    const webSocketRoot = process.env.REACT_APP_WEB_SOCKET_ROOT;
    if (webSocketRoot) {
        return webSocketRoot + webSocketPath;
    }
    const location = window.location;
    const webProtocol = location.protocol === "https:" ? "wss:" : "ws:";
    // Workaround to make sockets work in iOS captive portal browser
    let host = location.host;
    if (location.host === "captive.apple.com" && location.protocol === "http:") {
        host = "192.168.4.1"
    }
    return webProtocol + "//" + host + webSocketPath;
}
