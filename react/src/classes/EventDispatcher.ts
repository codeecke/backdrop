export class EventDispatcher {
  private listeners: Record<string, ((payload?: any) => void)[]> = {};

  addEventListener(eventName: string, cb: (payload?: any) => void) {
    if (!this.listeners[eventName]) {
      this.listeners[eventName] = [];
    }
    this.listeners[eventName].push(cb);
  }

  dispatchEvent(eventName: string, payload?: any) {
    if (!this.listeners[eventName]) return;
    this.listeners[eventName].forEach((cb) => cb(payload));
  }
}
