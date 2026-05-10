import grpc

from generated import database_pb2
from generated import database_pb2_grpc

logical_clock = 0

channel = grpc.insecure_channel('localhost:50051')

stub = database_pb2_grpc.DatabaseServiceStub(channel)

logical_clock += 1

response = stub.Put(
    database_pb2.PutRequest(
        key="usuario",
        value="Luis",
        timestamp=logical_clock
    )
)

logical_clock = response.timestamp

print(response.message)
print(f"Client Clock: {logical_clock}")

logical_clock += 1

response = stub.Get(
    database_pb2.GetRequest(
        key="usuario",
        timestamp=logical_clock
    )
)

logical_clock = response.timestamp

print("Value:", response.value)
print(f"Client Clock: {logical_clock}")