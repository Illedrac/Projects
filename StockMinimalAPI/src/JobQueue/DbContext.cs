using MongoDB.Bson.Serialization;
using MongoDB.Entities;

sealed class DbContext : DBContext
{
    public DbContext(string database, string host) : base(database, host)
    {
        var objectSerializer = new MongoDB.Bson.Serialization.Serializers.ObjectSerializer(type =>
            MongoDB.Bson.Serialization.Serializers.ObjectSerializer.DefaultAllowedTypes(type) ||
            type.FullName!.EndsWith("Command"));

        BsonSerializer.RegisterSerializer(objectSerializer);
    }
}