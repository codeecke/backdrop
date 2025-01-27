export class WebSocketEvent<T = unknown> {
  constructor(public readonly eventName: string, public readonly payload?: T) {}
}
