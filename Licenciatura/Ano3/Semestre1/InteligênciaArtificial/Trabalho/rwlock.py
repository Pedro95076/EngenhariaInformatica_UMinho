import threading

class ReadWriteLock:

    def __init__(self):
        self.reading = threading.Condition(threading.Lock(  ))
        self.readers = 0

    def racquire(self):
        self.reading.acquire(  )
        try:
            self.readers += 1
        finally:
            self.reading.release(  )

    def rrelease(self):
        self.reading.acquire(  )
        try:
            self.readers -= 1
            if not self.readers:
                self.reading.notifyAll(  )
        finally:
            self.reading.release(  )

    def wacquire(self):
        self.reading.acquire(  )
        while self.readers > 0:
            self.reading.wait(  )

    def wrelease(self):
        self.reading.release(  )