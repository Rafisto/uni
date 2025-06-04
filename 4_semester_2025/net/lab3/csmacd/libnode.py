import random
from enum import Enum


class NodeState(Enum):
    IDLE = "idle"
    TRANSMITTING = "transmitting"
    WAITING = "waiting"
    JAMMING = "jamming"
    BACKOFF = "backoff"
    SUCCESS = "success"


class Node:
    """
    Represents a part in a telecommunication medium, simulated as a node array.
    """

    def __init__(self, name: str, position: int, transmission_tick: float = -1) -> None:
        """
        Initialize a Node instance with basic parameters.
            name: Unique identifier for the node.
            position: Physical coordinate (x) of the node in the medium.
            send_time: Scheduled transmission tick for initial message.
        """
        self.name = name
        self.position = position

        self.transmission_tick = random.randint(
            0, 1000) if transmission_tick < 0 else transmission_tick
        self.state = NodeState.IDLE

        self.backoff = 0
        self.attempts = 0
        self.jam_start = 0

    def position(self) -> int:
        """
        Return the physical position of the node in the medium.
        """
        return self.position

    def __str__(self) -> str:
        """
        Return a human-readable string representation of the node.
        """
        return f"{self.name}(x={self.position})"

    def __repr__(self) -> str:
        """
        Return an unambiguous string representation of the node.
        """
        return (f"Node(name='{self.name}', position={self.position}, "
                f"send_time={self.transmission_tick})")
