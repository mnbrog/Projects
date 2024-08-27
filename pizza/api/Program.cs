using decorator;

ChicageStyle chitown = new ChicageStyle();
chitown.setSize("Large");
chitown = new cheese(chitown);
chitown = new cheese(chitown);
chitown = new sausage(chitown);
System.Console.WriteLine($"{chitown.getDiscription()} cost ${chitown.cost()}");