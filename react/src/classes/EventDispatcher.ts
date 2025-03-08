export class EventDispatcher<T = any> {
  private listeners: Record<string, ((payload?: T) => void)[]> = {};

  addEventListener(eventName: string, cb: (payload?: T) => void) {
    if (!this.listeners[eventName]) {
      this.listeners[eventName] = [];
    }
    this.listeners[eventName].push(cb);
  }

  dispatchEvent(eventName: string, payload?: T) {
    if (!this.listeners[eventName]) return;
    this.listeners[eventName].forEach((cb) => cb(payload));
  }
}
