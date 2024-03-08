using FastEndpoints;
using FastEndpoints.Swagger;

var bld = WebApplication.CreateBuilder();

bld.Services
   .AddFastEndpoints()
   .SwaggerDocument()
   .AddJobQueues<JobRecord, JobProvider>()
   .AddAWSLambdaHosting(LambdaEventSource.RestApi);

var app = bld.Build();

app.UseFastEndpoints()
   .UseHttpsRedirection()
   .UseSwaggerGen()
   .UseJobQueues( o =>
   {
       o.ExecutionTimeLimit = TimeSpan.FromSeconds(10);
   });

app.Run();
