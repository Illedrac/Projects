using FastEndpoints;
using FastEndpoints.Swagger;

var bld = WebApplication.CreateBuilder();

bld.Services
   .AddSingleton(new DbContext("JobStoreDatabase", "localhost"))
   .AddFastEndpoints()
   .SwaggerDocument()
   .AddJobQueues<JobRecord, JobProvider>();

var app = bld.Build();

app.UseFastEndpoints()
   .UseHttpsRedirection()
   .UseSwaggerGen()
   .UseJobQueues();

app.Run();
