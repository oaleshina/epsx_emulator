#include "pscx_bios.h"

#include <fstream>
#include <iterator>

//------------------------------------------------
// TODO : to implement the loadBios function.
// It should load the BIOS binary file into array of bytes u8 (m_data).
//
// Rust:
// pub fn new(path: &Path) -> Result<Bios> {
//    let file = try!(File::open(path));
//
//    let mut data = Vec::new();
//
//    Load the BIOS
//    try!(file.take(BIOS_SIZE).read_to_end(&mut data));
//
//    if data.len() == BIOS_SIZE as usize {
//       Ok(Bios { data: data })
//    } else {
//       Err(Error::new(ErrorKind::InvalidInput,
//                      "Invalid_BIOS_size"))
//    } 
//--------------------------------------------------
Bios::BiosState Bios::loadBios(std::string path)
{
	std::basic_ifstream<uint8_t> biosFile(path, std::ios::in | std::ios::binary);

	if (!biosFile.good())
		return BIOS_STATE_INCORRECT_FILENAME;

	const uint32_t biosSize = 512 * 1024; // 512 kb

										  // Load the BIOS
	m_data.insert(m_data.begin(), std::istreambuf_iterator<uint8_t>(biosFile), std::istreambuf_iterator<uint8_t>());

	biosFile.close();

	if (m_data.size() != biosSize)
		return BIOS_STATE_INVALID_BIOS_SIZE;
}

uint32_t Bios::load32(uint32_t offset)
{
	uint32_t b0 = m_data[offset + 0];
	uint32_t b1 = m_data[offset + 1];
	uint32_t b2 = m_data[offset + 2];
	uint32_t b3 = m_data[offset + 3];

	return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}