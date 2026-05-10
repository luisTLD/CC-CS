from concurrent import futures
import grpc

from generated import database_pb2
from generated import database_pb2_grpc

database = {}

logical_clock = 0

class DatabaseService(database_pb2_grpc.DatabaseServiceServicer):

    def update_clock(self, received_timestamp):
        global logical_clock

        logical_clock = max(logical_clock, received_timestamp) + 1

        return logical_clock

    def Put(self, request, context):
        pass

    def Get(self, request, context):
        pass

    def Replicate(self, request, context):

        current_clock = self.update_clock(request.timestamp)

        database[request.key] = request.value

        print(f"[REPLICA NODE][Clock {current_clock}] {request.key} = {request.value}")

        return database_pb2.ReplicationResponse(
            message="Replication successful"
        )

def serve():

    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))

    database_pb2_grpc.add_DatabaseServiceServicer_to_server(
        DatabaseService(),
        server
    )

    server.add_insecure_port('[::]:50052')

    print("Replica Node running on port 50052")

    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    serve()