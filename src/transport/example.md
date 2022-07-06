System.setup() {

}

System.enroll(Stream* s) {
auto m = co_await s.read();
if (m == auth) {

}

for (;;) {
m = s.read();
handlers.process(m);
}
}

System.shutdown() {

}

