int MPI_Send(
    void*            buf        /* in  */,
    int              count      /* in  */,
    MPI_Datatype     datatype   /* in  */,
    int              dest       /* in  */,
    int              tag        /* in  */,
    MPI_Comm         comm       /* in  */);