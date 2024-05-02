int MPI_Recv(
    void*            buf          /* in  */,
    int              count        /* in  */,
    MPI_Datatype     datatype     /* in  */,
    int              source       /* in  */,
    int              tag          /* in  */,
    MPI_Comm         comm         /* in  */,
    MPI_Status       status       /* out */);