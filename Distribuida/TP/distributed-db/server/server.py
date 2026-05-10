from concurrent import futures
import grpc

from generated import database_pb2
from generated import database_pb2_grpc

database = {}

logical_clock = 0

REPLICA_ADDRESS = 'localhost:50052'

class DatabaseService(database_pb2_grpc.DatabaseServiceServicer):

    def update_clock(self, received_timestamp):
        global logical_clock

        logical_clock = max(logical_clock, received_timestamp) + 1

        return logical_clock

    def replicate_data(self, key, value, timestamp):

        try:
            channel = grpc.insecure_channel(REPLICA_ADDRESS)

            stub = database_pb2_grpc.DatabaseServiceStub(channel)

            response = stub.Replicate(
                database_pb2.ReplicationRequest(
                    key=key,
                    value=value,
                    timestamp=timestamp
                )
            )

            print(f"[REPLICATION] Data replicated to replica node")

        except Exception as e:
            print(f"[ERROR] Replication failed: {e}")

    def Put(self, request, context):

        current_clock = self.update_clock(request.timestamp)

        database[request.key] = request.value

        print(f"[LEADER][Clock {current_clock}] PUT {request.key} = {request.value}")

        self.replicate_data(
            request.key,
            request.value,
            current_clock
        )

        return database_pb2.PutResponse(
            message="Data stored successfully",
            timestamp=current_clock
        )

    def Get(self, request, context):

        current_clock = self.update_clock(request.timestamp)

        value = database.get(request.key, "")

        print(f"[LEADER][Clock {current_clock}] GET {request.key}")

        return database_pb2.GetResponse(
            value=value,
            timestamp=current_clock
        )

    def Replicate(self, request, context):

        current_clock = self.update_clock(request.timestamp)

        database[request.key] = request.value

        print(f"[REPLICA][Clock {current_clock}] REPLICATED {request.key} = {request.value}")

        return database_pb2.ReplicationResponse(
            message="Replication successful"
        )

def serve():

    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))

    database_pb2_grpc.add_DatabaseServiceServicer_to_server(
        DatabaseService(),
        server
    )

    server.add_insecure_port('[::]:50051')

    print("Leader Node running on port 50051")

    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    serve()