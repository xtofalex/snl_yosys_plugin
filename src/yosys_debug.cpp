#include "yosys_debug.h"

USING_YOSYS_NAMESPACE

void YosysDebug::print(const RTLIL::Wire* w, size_t indent, std::ostream& stream) {
  stream << std::string(indent, ' ') << "Wire:" << std::endl;
	stream << std::string(indent+2, ' ') << w->module->name.c_str() << std::endl;
	stream << std::string(indent+2, ' ') << w->name.c_str() << std::endl;
	stream << std::string(indent+2, ' ')
		<< "width:" << w->width << ", start_offset:" << w->start_offset << ", port_id:" << w->port_id
		<< std::endl;
	stream << std::string(indent+2, ' ')
		<< "port_input:" << w->port_output << ", port_output:" << w->port_output << ", upto:" << w->upto
		<< ", is_signed:" << w->is_signed
		<< std::endl;
}

void YosysDebug::print(const RTLIL::Cell* c, size_t indent, std::ostream& stream) {
  stream << std::string(indent, ' ') << "Cell:" << std::endl;
	stream << std::string(indent+2, ' ') << c->module->name.c_str() << std::endl;
	stream << std::string(indent+2, ' ') << c->name.c_str() << std::endl;
	stream << std::string(indent+2, ' ') << c->type.c_str() << std::endl;
	stream << std::string(indent+2, ' ') << "connections: " << c->connections().size() << std::endl;
	stream << std::string(indent+2, ' ') << "parameters: " << c->parameters.size() << std::endl;
  if (not c->parameters.empty()) {
    for (auto parameter: c->parameters) {
      YosysDebug::printParameter(parameter.first, parameter.second, 2, stream);
    }
  }
}

void YosysDebug::printParameter(const RTLIL::IdString& s, const RTLIL::Const& v, size_t indent, std::ostream& stream) {
  stream << std::string(indent, ' ') << "Parameter: ";
  stream << s.str() << ", " << v.as_string() << std::endl;
}

void YosysDebug::print(
  const RTLIL::IdString& id, const RTLIL::SigSpec& s,
  size_t indent, std::ostream& stream) {
  stream << std::string(indent, ' ') << "Connection:" << std::endl;
	stream << std::string(indent+2, ' ') << id.c_str() << std::endl;
	stream << std::string(indent+2, ' ') << s.size() << std::endl;
	stream << std::string(indent+2, ' ') << "chunks: " << s.chunks().size() << std::endl;
	stream << std::string(indent+2, ' ') << "bits: " << s.bits().size() << std::endl;
  if (not s.bits().empty()) {
    for (auto bit: s.bits()) {
      YosysDebug::print(bit, indent+2, stream);
    }
  }
}

void YosysDebug::print(const RTLIL::SigBit& b, size_t indent, std::ostream& stream) {
  stream << std::string(indent, ' ') << "Bit:";
  if (b.wire) {
    stream << " wire:" << b.wire->name.c_str() << ", offset: " << b.offset << std::endl;
  } else { 
    stream << " data:" << b.data << std::endl;
  }
}
