void serialize_Example(void *arg) {
  Example *v = (Example *)arg;
  serialize_string((void *)v->name);
  serialize_int32_array((void *)v->iarray);
  serialize_float32_array((void *)v->farray);
}
void serialize_Message(void *arg) {
  Message *v = (Message *)arg;
  serialize_string((void *)v->name);
  serialize_string((void *)v->message);
}
void serialize_Image(void *arg) {
  Image *v = (Image *)arg;
  serialize_Header((void *)v->header);
  serialize_uint32((void *)v->height);
  serialize_uint32((void *)v->width);
  serialize_string((void *)v->encoding);
  serialize_uint8((void *)v->is_bigendian);
  serialize_uint32((void *)v->step);
  serialize_uint8_array((void *)v->data);
}
void serialize_Header(void *arg) {
  Header *v = (Header *)arg;
  serialize_uint32((void *)v->seq);
  serialize_time((void *)v->stamp);
  serialize_string((void *)v->frame_id);
}
